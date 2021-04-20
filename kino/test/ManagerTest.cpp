#include <boost/test/unit_test.hpp>
#include "HallManager.h"
#include "MovieManager.h"
#include "TicketManager.h"
#include "ClientManager.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect3)

BOOST_AUTO_TEST_CASE(ClientManagerCase)
{
	ClientManager cm;
	BOOST_REQUIRE_EQUAL(cm.countClients(), 0);
	BOOST_REQUIRE_EQUAL(cm.createClient("1", "Jan", "Kowalski", 21, "jk@a.pl", "333444134"), true);
	BOOST_REQUIRE_EQUAL(cm.createClient("2", "Arek", "Nowak", 60, "an@a.pl", "123321123"), true);
	BOOST_REQUIRE_EQUAL(cm.countClients(), 2);
	clientPtr cl(new Client("3", "Marek", "Heszko", 30, "mh@b.pl", "333211456"));
	BOOST_REQUIRE_EQUAL(cm.createClient(cl), true);
	BOOST_REQUIRE_EQUAL(cm.countClients(), 3);
	BOOST_TEST_MESSAGE(cm.getClientsInfo());
	BOOST_TEST_MESSAGE(cm.getClientsTicketsInfo("1"));
	BOOST_REQUIRE_EQUAL(cm.removeClient("2"), true);
	BOOST_REQUIRE_EQUAL(cm.removeClient(cl), true);
	BOOST_REQUIRE_EQUAL(cm.countClients(), 1);
}

BOOST_AUTO_TEST_CASE(HallManagerCase)
{
	HallManager hm;
	BOOST_REQUIRE_EQUAL(hm.countHall(), 0);
	BOOST_REQUIRE_EQUAL(hm.createHall("1", "Kinder", 20, 10, false), true);
	BOOST_REQUIRE_EQUAL(hm.createHall("2", "Tarczynski", 10, 20, true), true);
	BOOST_REQUIRE_EQUAL(hm.createHall("3", "Audi", 12, 13, false), true);
	BOOST_REQUIRE_EQUAL(hm.countHall(), 3);
	hallPtr hall(new Hall("4", "Samsung", 32, 3, true));
	BOOST_REQUIRE_EQUAL(hm.createHall(hall), true);
	BOOST_TEST_MESSAGE(hm.getHallsInfo());
	BOOST_REQUIRE_EQUAL(hm.countHall(), 4);
	BOOST_REQUIRE_EQUAL(hm.removeHall("2"), true);
	BOOST_REQUIRE_EQUAL(hm.removeHall(hall), true);
	BOOST_REQUIRE_EQUAL(hm.countHall(), 2);

	MovieManager mm;
	BOOST_REQUIRE_EQUAL(mm.createMovie("1", "Terminator", 120, "AD", "horror", 8.2), true);
	BOOST_REQUIRE_EQUAL(mm.createMovie("2", "Terminator2", 156, "AD", "horror", 7.2), true);
	BOOST_REQUIRE_EQUAL(mm.createMovie("3", "Terminator3", 98, "AD", "horror", 4.7), true);
	moviePtr movie(new Movie("4", "Terminator4", 102, "AD", "horror", 9.2));
	BOOST_REQUIRE_EQUAL(hm.addMovieToHall("1", movie), true);
	BOOST_REQUIRE_EQUAL(hm.addMovieToHall("3", mm("1")), true);
	BOOST_TEST_MESSAGE(hm.getMoviesInHallInfo("1"));
}
BOOST_AUTO_TEST_CASE(MovieManagerCase)
{
	MovieManager mm;
	BOOST_REQUIRE_EQUAL(mm.countMovies(), 0);
	BOOST_REQUIRE_EQUAL(mm.createMovie("1", "Terminator", 120, "AD", "horror", 8.2), true);
	BOOST_REQUIRE_EQUAL(mm.createMovie("2", "Terminator2", 156, "AD", "horror", 7.2), true);
	BOOST_REQUIRE_EQUAL(mm.createMovie("3", "Terminator3", 98, "AD", "horror", 4.7), true);
	BOOST_REQUIRE_EQUAL(mm.countMovies(), 3);
	moviePtr movie(new Movie("4", "Terminator4", 102, "AD", "horror", 9.2));
	BOOST_REQUIRE_EQUAL(mm.createMovie(movie), true);
	BOOST_TEST_MESSAGE(mm.getMoviesInfo());
	BOOST_REQUIRE_EQUAL(mm.countMovies(), 4);
	BOOST_REQUIRE_EQUAL(mm.removeMovie("2"), true);
	BOOST_REQUIRE_EQUAL(mm.removeMovie(movie), true);
	BOOST_REQUIRE_EQUAL(mm.countMovies(), 2);

	HallManager hm;
	BOOST_REQUIRE_EQUAL(hm.createHall("1", "Kinder", 20, 10, false), true);
	BOOST_REQUIRE_EQUAL(hm.createHall("2", "Tarczynski", 10, 20, true), true);
	BOOST_REQUIRE_EQUAL(hm.createHall("3", "Audi", 12, 13, false), true);
	hallPtr hall(new Hall("4", "Samsung", 32, 3, true));
	BOOST_REQUIRE_EQUAL(mm.addHallToMovie("1", hall), true);
	BOOST_REQUIRE_EQUAL(mm.addHallToMovie("3", hm("1")), true);
	BOOST_TEST_MESSAGE(mm.getMoviesHallInfo("1"));
}

BOOST_AUTO_TEST_CASE(TicketManagerCase)
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);

	MovieManager mm;
	BOOST_REQUIRE_EQUAL(mm.createMovie("1", "Terminator", 120, "AD", "horror", 8.2), true);
	BOOST_REQUIRE_EQUAL(mm.createMovie("2", "Terminator2", 156, "AD", "horror", 7.2), true);
	BOOST_REQUIRE_EQUAL(mm.createMovie("3", "Terminator3", 98, "AD", "horror", 4.7), true);
	moviePtr movie1(new Movie("4", "Terminator4", 102, "AD", "horror", 9.2));
	BOOST_REQUIRE_EQUAL(mm.createMovie(movie1), true);
	HallManager hm;
	BOOST_REQUIRE_EQUAL(hm.createHall("1", "Kinder", 20, 10, false), true);
	BOOST_REQUIRE_EQUAL(hm.createHall("2", "Tarczynski", 10, 20, true), true);
	BOOST_REQUIRE_EQUAL(hm.createHall("3", "Audi", 12, 13, false), true);
	hallPtr hall1(new Hall("4", "Samsung", 32, 3, true));
	ClientManager cm;
	BOOST_REQUIRE_EQUAL(cm.createClient("1", "Jan", "Kowalski", 21, "jk@a.pl", "333444134"), true);
	BOOST_REQUIRE_EQUAL(cm.createClient("2", "Arek", "Nowak", 70, "an@a.pl", "123321123"), true);
	clientPtr client1(new Client("3", "Marek", "Heszko", 20, "mh@b.pl", "333211456"));

	TicketManager tm;
	BOOST_REQUIRE_EQUAL(tm.countShowtimes(), 0);
	tm.create10Showtimes(const_cast<std::vector<moviePtr> &>(mm.getElements()),
						 const_cast<std::vector<hallPtr> &>(hm.getElements()));
	BOOST_TEST_MESSAGE(tm.getShowtimesInfo());
	BOOST_REQUIRE_EQUAL(tm.countShowtimes(), 10);
	tm.create10Showtimes(const_cast<std::vector<moviePtr> &>(mm.getElements()),
						 const_cast<std::vector<hallPtr> &>(hm.getElements()));
	tm.create10Showtimes(const_cast<std::vector<moviePtr> &>(mm.getElements()),
						 const_cast<std::vector<hallPtr> &>(hm.getElements()));
	tm.create10Showtimes(const_cast<std::vector<moviePtr> &>(mm.getElements()),
						 const_cast<std::vector<hallPtr> &>(hm.getElements()));
	tm.updateShowtimes();
	showtimePtr sh1(new Showtime("99", LT, movie1, hall1, 25));
	BOOST_REQUIRE_EQUAL(tm.createShowtime(sh1), true);
	BOOST_REQUIRE_EQUAL(tm.countShowtimes(), 41);

	/*boost::posix_time::time_duration time_duration(24, 0, 0, 0);					//test odnosnie update'u starych seansow, aby test zadzialal nalezy zakomentowac if pliku Showtime.cpp linia 27
	showtimePtr showtime1(new Showtime("99",LT-time_duration,movie1,hall1,25));
	BOOST_REQUIRE_EQUAL(tm.createShowtime(showtime1),true);
	BOOST_REQUIRE_EQUAL(tm.countShowtimes(),41);
	BOOST_TEST_MESSAGE(tm.getShowtimesInfo());
	tm.updateShowtimes();
	BOOST_REQUIRE_EQUAL(tm.countShowtimes(),40); */

	boost::posix_time::time_duration time_duration2(60, 0, 0, 0);
	ticketPtr ticket1(new Ticket(tm.getShowtimeFromID("2")->getFreeRow(),
								 tm.getShowtimeFromID("2")->getFreeSeat(tm.getShowtimeFromID("2")->getFreeRow()),
								 tm.getShowtimeFromID("2"),
								 cm("1")));
	BOOST_REQUIRE_EQUAL(tm.createTicket("Terminator2", LT, client1), true);
	BOOST_REQUIRE_EQUAL(tm.createTicket("Terminator", LT, cm("2")), true);
	BOOST_REQUIRE_EQUAL(tm.createTicket(movie1, LT, cm("2")), true);
	//BOOST_REQUIRE_EQUAL(tm.createTicket("Terminator", LT + time_duration2, cm("2")), true);		//pokazanie, ze klient moze kupic bilet na ten sam film tyle, ze w pozniejszym czasie (linia ta zalezy od funckji random, co kilkanascie testow zdarza sie przypadek ze nie ma juz pozniejszego seansu)
	BOOST_REQUIRE_EQUAL(client1->getTicket(mm("2"), LT)->getPrice(),
						tm.getShowtimeFromID(client1->getTicket(mm("2"), LT)->getShowtime()->getId())->getPrice() - 8);
	BOOST_TEST_MESSAGE(client1->getClientsTicketsInfo());
	BOOST_REQUIRE_EQUAL(tm.createTicket(ticket1), true);
	BOOST_REQUIRE_EQUAL(tm.countTickets(), 4);
	BOOST_REQUIRE_EQUAL(tm.countOldTickets(), 0);
	BOOST_TEST_MESSAGE(tm.getTicketsInfo());
	BOOST_REQUIRE_EQUAL(tm.removeTicket(ticket1), true);
	BOOST_REQUIRE_EQUAL(tm.removeTicket(client1->getTicket(mm("2"), LT)), true);
	BOOST_REQUIRE_EQUAL(tm.countTickets(), 2);
	tm.updateTickets();
	BOOST_REQUIRE_EQUAL(tm.countTickets(), 2);
	BOOST_REQUIRE_EQUAL(tm.countOldTickets(), 0);
}

BOOST_AUTO_TEST_SUITE_END()