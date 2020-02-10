#include <boost/test/unit_test.hpp>
#include "ShowtimeRepository.h"
#include "TicketManager.h"
#include "ParameterException.h"
#include "AvaliableException.h"
#include "DuplicateException.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect4)

BOOST_AUTO_TEST_CASE(ParameterExceptionCase)
{
	BOOST_REQUIRE_THROW(Client("", "Jakub", "Wawrzyniak", 5, "224450@edu.p.lodz.pl", "123456789"), ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "", "Wawrzyniak", 5, "224450@edu.p.lodz.pl", "123456789"), ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "Jakub", "", 5, "224450@edu.p.lodz.pl", "123456789"), ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "Jakub", "Wawrzyniak", -1, "224450@edu.p.lodz.pl", "123456789"),
						ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "Jakub", "Wawrzyniak", 5, "", "123456789"), ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "Jakub", "Wawrzyniak", 5, "224450@edu.p.lodz.pl", ""), ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "Jakub", "Wawrzyniak", 5, "224450@edu.p.lodz.pl", "0123456789"),
						ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "Jakub", "Wawrzyniak", 1000, "224450@edu.p.lodz.pl", "123456789"),
						ParameterException);
	BOOST_REQUIRE_THROW(Client("c1", "1.<#$", "Wawrzyniak21235", 5, "224450@edu.p.lodz.pl", "123456789"),
						ParameterException);

	BOOST_REQUIRE_THROW(Hall("", "Kinder Bueno", 10, 10, true), ParameterException);
	BOOST_REQUIRE_THROW(Hall("h1", "", 10, 10, true), ParameterException);
	BOOST_REQUIRE_THROW(Hall("h1", "Kinder Bueno", -10, 10, true), ParameterException);
	BOOST_REQUIRE_THROW(Hall("h1", "Kinder Bueno", 10, -10, true), ParameterException);
	BOOST_REQUIRE_THROW(Hall("h1", "Kinder Bueno", 0, 10, true), ParameterException);
	BOOST_REQUIRE_THROW(Hall("h1", "Kinder Bueno", 10, 1000, true), ParameterException);
	BOOST_REQUIRE_THROW(Hall("h1", "Kinder Bueno", 1000, 10, true), ParameterException);

	BOOST_REQUIRE_THROW(Movie("h1", "Avatar", 180, "Jakub Wawrzyniak", "fantasy", 19.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("h1", "Avatar", -180, "Jakub Wawrzyniak", "fantasy", 9.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("", "Avatar", 180, "Jakub Wawrzyniak", "fantasy", 9.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("h1", "Avatar", 180, "!@#$%^&*1234567890", "fantasy", 9.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("h1", "", 180, "Jakub Wawrzyniak", "fantasy", 9.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("h1", "Avatar", 0, "Jakub Wawrzyniak", "fantasy", 9.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("h1", "Avatar", 180, "", "fantasy", 9.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("h1", "Avatar", 180, "Jakub Wawrzyniak", "", 9.0), ParameterException);
	BOOST_REQUIRE_THROW(Movie("h1", "Avatar", 180, "Jakub Wawrzyniak", "matematyka", 9.0), ParameterException);

	boost::posix_time::time_duration time_duration(30, 0, 0, 0);
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	hallPtr h1(new Hall("h1", "Kinder Bueno", 10, 10, true));
	moviePtr m1(new Movie("h1", "Avatar", 180, "Jakub Wawrzyniak", "fantasy", 9.0));
	BOOST_REQUIRE_THROW(Showtime("h1", LT, m1, h1, -12), ParameterException);
	BOOST_REQUIRE_THROW(Showtime("", LT, m1, h1, 12), ParameterException);
	BOOST_REQUIRE_THROW(Showtime("h1", LT, std::shared_ptr<Movie>(nullptr), h1, 12), ParameterException);
	BOOST_REQUIRE_THROW(Showtime("h1", LT - time_duration, m1, h1, 12), ParameterException);
	clientPtr c1(new Client("c1", "Jakub", "Wawrzyniak", 5, "224450@edu.p.lodz.pl", "123456789"));
	showtimePtr sh1(new Showtime("h1", LT, m1, h1, 12));
	BOOST_REQUIRE_THROW(Ticket(-1, 2, sh1, c1), ParameterException);
	BOOST_REQUIRE_THROW(Ticket(1, -2, sh1, c1), ParameterException);
	BOOST_REQUIRE_THROW(Ticket(1000, 2, sh1, c1), ParameterException);
	BOOST_REQUIRE_THROW(Ticket(1, 1000, sh1, c1), ParameterException);
}

BOOST_AUTO_TEST_CASE(AvaliableExceptionCase)
{
	clientPtr c1(new Client("c1", "Jakub", "Wawrzyniak", 5, "224450@edu.p.lodz.pl", "123456789"));
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	hallPtr h1(new Hall("h1", "Kinder Bueno", 1, 1, true));
	moviePtr m1(new Movie("m1", "Avatar", 180, "Jakub Wawrzyniak", "fantasy", 9.0));
	showtimePtr sh1(new Showtime("h1", LT, m1, h1, 10));
	ticketPtr t1(new Ticket(1, 1, sh1, c1));
	TicketManager tm;
	ShowtimeRepository shr;
	tm.createShowtime(sh1);
	tm.createTicket("Avatar", LT, c1);
	BOOST_REQUIRE_THROW(sh1->getFreeRow(), AvaliableException);
	BOOST_REQUIRE_THROW(sh1->getFreeSeat(1), AvaliableException);
	BOOST_REQUIRE_THROW(shr.find("yrt"), AvaliableException);
	BOOST_REQUIRE_THROW(shr.getElement(100),
						AvaliableException);
	moviePtr m2(new Movie("m2", "Avatar 2", 180, "Jakub Wawrzyniak", "fantasy", 9.0));
	BOOST_REQUIRE_THROW(shr.findWithMovie("Avatar 2", LT), AvaliableException);
	BOOST_REQUIRE_THROW(shr.findWithMovie(m2, LT), AvaliableException);
	BOOST_REQUIRE_THROW(shr.find("error"), AvaliableException);
	BOOST_REQUIRE_THROW(c1->getTicket(m2, LT), AvaliableException);

	ClientRepository cr;
	BOOST_REQUIRE_THROW(cr.find("yrt"), AvaliableException);
	BOOST_REQUIRE_THROW(cr.getElement(100), AvaliableException);

	MovieRepository mr;
	BOOST_REQUIRE_THROW(mr.find("yrt"), AvaliableException);
	BOOST_REQUIRE_THROW(mr.getElement(100), AvaliableException);

	HallRepository hr;
	BOOST_REQUIRE_THROW(hr.find("yrt"), AvaliableException);
	BOOST_REQUIRE_THROW(hr.getElement(100), AvaliableException);

	TicketRepository tr;
	BOOST_REQUIRE_THROW(tr.find("yrt"), AvaliableException);
	BOOST_REQUIRE_THROW(tr.getElement(100), AvaliableException);
}

BOOST_AUTO_TEST_CASE(DuplicateExceptionCase)
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	clientPtr c1(new Client("c1", "Jakub", "Wawrzyniak", 5, "224450@edu.p.lodz.pl", "123456789"));
	hallPtr h1(new Hall("h1", "Kinder Bueno", 10, 10, true));
	moviePtr m1(new Movie("h1", "Avatar", 180, "Jakub Wawrzyniak", "fantasy", 9.0));
	showtimePtr sh1(new Showtime("sh1", LT, m1, h1, 12));
	ticketPtr t1(new Ticket(1, 1, sh1, c1));
	ShowtimeRepository shr;
	shr.create(sh1);
	ClientRepository cr;
	cr.create(c1);
	HallRepository hr;
	hr.create(h1);
	MovieRepository mr;
	mr.create(m1);
	TicketRepository tr;
	tr.create(t1);
	BOOST_REQUIRE_THROW(shr.create(sh1), DuplicateException);
	BOOST_REQUIRE_THROW(mr.create(m1), DuplicateException);
	BOOST_REQUIRE_THROW(cr.create(c1), DuplicateException);
	BOOST_REQUIRE_THROW(tr.create(t1), DuplicateException);
	BOOST_REQUIRE_THROW(hr.create(h1), DuplicateException);
	TicketManager tm;
	tm.createShowtime(sh1);
	tm.createTicket("Avatar", LT, c1);
	BOOST_REQUIRE_THROW(tm.createTicket("Avatar", LT, c1), DuplicateException);

}

BOOST_AUTO_TEST_SUITE_END()
