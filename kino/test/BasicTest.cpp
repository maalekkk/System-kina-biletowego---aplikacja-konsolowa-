#include <boost/test/unit_test.hpp>
#include "Client.h"
#include "Hall.h"
#include "Movie.h"
#include "Ticket.h"
#include "Showtime.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect1)

BOOST_AUTO_TEST_CASE(ClientCase)
{
	clientPtr client1(new Client("1", "Jan", "Kowalski", 30, "jan.kowalski@gmail.com", "555111333"));
	BOOST_REQUIRE_EQUAL(client1->getId(), "1");
	BOOST_REQUIRE_EQUAL(client1->getFirstName(), "Jan");
	BOOST_REQUIRE_EQUAL(client1->getLastName(), "Kowalski");
	BOOST_REQUIRE_EQUAL(client1->getAge(), 30);
	BOOST_REQUIRE_EQUAL(client1->getEmail(), "jan.kowalski@gmail.com");
	BOOST_REQUIRE_EQUAL(client1->getPhoneNumber(), "555111333");
	BOOST_REQUIRE_EQUAL(client1->getTicketsSize(), 0);

	moviePtr movie1(new Movie("1", "Joker", 122, "Todd Phillips", "dramat", 8.5));
	hallPtr hall1(new Hall("1", "Kinder Bueno", 10, 8, false));
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	boost::posix_time::time_duration td(120, 0, 0, 0);
	showtimePtr showtime1(new Showtime("1", LT + td, movie1, hall1, 20));
	ticketPtr ticket1
		(new Ticket(showtime1->getFreeRow(), showtime1->getFreeSeat(showtime1->getFreeRow()), showtime1, client1));
	client1->addTicket(ticket1);
	BOOST_REQUIRE_EQUAL(client1->getTicket(movie1, LT + td), ticket1);
	BOOST_REQUIRE_EQUAL(client1->getTicketsSize(), 1);
	BOOST_REQUIRE_EQUAL(client1->getThisMonthTicketsSize(), 1);
	BOOST_TEST_MESSAGE(client1->getClientsTicketsInfo());
	client1->removeTicket(ticket1);
	BOOST_REQUIRE_EQUAL(client1->getTicketsSize(), 0);
	BOOST_REQUIRE_EQUAL(client1->getThisMonthTicketsSize(), 0);

	//Testowanie konta normalnego i premium
	client1->setType(1);        //1 bilet do kina w obecnym miesiacu
	BOOST_REQUIRE_EQUAL(client1->getClientType()->discount(10), 10);
	client1->setType(10);        //10 biletow do kina w obecnym miesiacu
	BOOST_REQUIRE_EQUAL(client1->getClientType()->discount(10), 8);

	BOOST_TEST_MESSAGE(client1->getInfo());
}

BOOST_AUTO_TEST_CASE(HallCase)
{
	Hall hall1("1", "Kinder Bueno", 10, 8, false);
	BOOST_REQUIRE_EQUAL(hall1.getId(), "1");
	BOOST_REQUIRE_EQUAL(hall1.getName(), "Kinder Bueno");
	BOOST_REQUIRE_EQUAL(hall1.getAvailable3D(), false);
	BOOST_REQUIRE_EQUAL(hall1.getRows(), 10);
	BOOST_REQUIRE_EQUAL(hall1.getSeatsInRow(), 8);
	BOOST_REQUIRE_EQUAL(hall1.getSize(), 80);
	BOOST_REQUIRE_EQUAL(hall1.getNumberOfMovies(), 0);
	moviePtr movie1(new Movie("1", "Joker", 122, "Todd Phillips", "dramat", 8.5));
	BOOST_REQUIRE_EQUAL(hall1.addMovie(movie1), true);
	BOOST_TEST_MESSAGE(hall1.getMoviesInHallInfo());
	BOOST_REQUIRE_EQUAL(hall1.getNumberOfMovies(), 1);
	BOOST_REQUIRE_EQUAL(hall1.removeMovie(movie1), true);
	BOOST_REQUIRE_EQUAL(hall1.getNumberOfMovies(), 0);
	BOOST_TEST_MESSAGE(hall1.getInfo());
}

BOOST_AUTO_TEST_CASE(MovieCase)
{
	Movie movie1("1", "Joker", 122, "Todd Phillips", "dramat", 8.5);
	BOOST_REQUIRE_EQUAL(movie1.getId(), "1");
	BOOST_REQUIRE_EQUAL(movie1.getTitle(), "Joker");
	BOOST_REQUIRE_EQUAL(movie1.getDuration(), 122);
	BOOST_REQUIRE_EQUAL(movie1.getDirector(), "Todd Phillips");
	BOOST_REQUIRE_EQUAL(movie1.getType(), "dramat");
	BOOST_REQUIRE_EQUAL(movie1.getRating(), 8.5);
	BOOST_REQUIRE_EQUAL(movie1.getNumberOfHalls(), 0);
	hallPtr hall1(new Hall("1", "Kinder Bueno", 10, 8, false));
	BOOST_REQUIRE_EQUAL(movie1.addHall(hall1), true);
	BOOST_REQUIRE_EQUAL(movie1.getNumberOfHalls(), 1);
	BOOST_TEST_MESSAGE(movie1.getMoviesHallInfo());
	BOOST_REQUIRE_EQUAL(movie1.removeHall(hall1), true);
	BOOST_REQUIRE_EQUAL(movie1.getNumberOfHalls(), 0);
	BOOST_TEST_MESSAGE(movie1.getInfo());
}

BOOST_AUTO_TEST_CASE(TicketCase)
{
	clientPtr client1(new Client("1", "Jan", "Kowalski", 22, "jan.kowalski@gmail.com", "555111333"));        //student
	moviePtr movie1(new Movie("1", "Joker", 122, "Todd Phillips", "dramat", 8.5));
	hallPtr hall1(new Hall("1", "Kinder Bueno", 10, 8, false));

	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	boost::posix_time::time_duration td(120, 0, 0, 0);
	showtimePtr showtime1(new Showtime("1", LT + td, movie1, hall1, 20));

	Ticket ticket1(showtime1->getFreeRow(), showtime1->getFreeSeat(showtime1->getFreeRow()), showtime1, client1);

	BOOST_REQUIRE_EQUAL(ticket1.getRow(), 10);
	BOOST_REQUIRE_EQUAL(ticket1.getSeat(), 8);
	BOOST_REQUIRE_EQUAL(ticket1.getClient()->getId(), "1");
	BOOST_REQUIRE_EQUAL(ticket1.getPrice(), 12);
	BOOST_REQUIRE_EQUAL(ticket1.getShowtime()->getId(), "1");
	BOOST_REQUIRE_EQUAL(ticket1.getBuyTime().is_not_a_date_time(), false);
	BOOST_TEST_MESSAGE(ticket1.getTicketType()->getInfo());
	BOOST_REQUIRE_NE(boost::uuids::to_string(ticket1.getId()), "");

	BOOST_TEST_MESSAGE(ticket1.getInfo());
}

BOOST_AUTO_TEST_CASE(ShowtimeCase)
{
	moviePtr movie1(new Movie("1", "Joker", 122, "Todd Phillips", "dramat", 8.5));
	hallPtr hall1(new Hall("1", "Kinder Bueno", 10, 8, false));

	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	boost::posix_time::time_duration td(120, 0, 0, 0);
	Showtime showtime1("1", LT + td, movie1, hall1, 20);

	BOOST_REQUIRE_EQUAL(showtime1.getId(), "1");
	BOOST_REQUIRE_EQUAL(showtime1.getPrice(), 20);
	BOOST_REQUIRE_EQUAL(showtime1.getNumberOfSeats(), 80);
	BOOST_REQUIRE_EQUAL(showtime1.getMovie()->getTitle(), "Joker");
	BOOST_REQUIRE_EQUAL(showtime1.getHall()->getName(), "Kinder Bueno");
	BOOST_REQUIRE_EQUAL(showtime1.getFreeRow(), 10);
	BOOST_REQUIRE_EQUAL(showtime1.getFreeSeat(showtime1.getFreeRow()), 8);
	BOOST_REQUIRE_EQUAL(showtime1.getNumberOfSeats(), 79);
	BOOST_REQUIRE_EQUAL(showtime1.getShowtimeStart().is_not_a_date_time(), false);

	BOOST_TEST_MESSAGE(showtime1.getInfo());
}

BOOST_AUTO_TEST_SUITE_END()