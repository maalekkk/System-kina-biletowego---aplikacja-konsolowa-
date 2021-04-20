#include <boost/test/unit_test.hpp>
#include "HallRepository.h"
#include "MovieRepository.h"
#include "TicketRepository.h"
#include "ShowtimeRepository.h"
#include "ClientRepository.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect2)

BOOST_AUTO_TEST_CASE(ClientRepositoryCase)
{
	clientPtr cl1(new Client("1", "Jan", "Nowak", 21, "jn@p.pl", "111222333"));
	clientPtr cl2(new Client("2", "Heniek", "Kowalski", 78, "hk@p.pl", "444555666"));
	clientPtr cl3(new Client("3", "Marek", "Rutek", 32, "mr@b.pl", "777888999"));
	ClientRepository cr;
	BOOST_REQUIRE_EQUAL(cr.create(cl1), true);
	BOOST_REQUIRE_EQUAL(cr.create(cl2), true);
	BOOST_REQUIRE_EQUAL(cr.create(cl3), true);
	BOOST_TEST_MESSAGE(cr.getInfo());
	BOOST_REQUIRE_EQUAL(cr.getSize(), 3);
	BOOST_REQUIRE_EQUAL(cr.remove(cl2), true);
	BOOST_REQUIRE_EQUAL(cr.getSize(), 2);
	BOOST_REQUIRE_EQUAL(cr.find("1"), cl1);
	BOOST_REQUIRE_EQUAL(cr.getElement(0), cl1);
	cr.clear();
	BOOST_REQUIRE_EQUAL(cr.getSize(), 0);
}
BOOST_AUTO_TEST_CASE(MovieRepositoryCase)
{
	moviePtr m1(new Movie("1", "Terminator", 180, "Jakub Wawrzyniak", "akcji", 9.0));
	moviePtr m2(new Movie("2", "Terminator 2", 190, "Jakub Wawrzyniak", "dramat", 5.0));
	moviePtr m3(new Movie("3", "Terminator 3", 170, "Jakub Wawrzyniak", "komedia", 2.0));
	MovieRepository mr;
	BOOST_REQUIRE_EQUAL(mr.create(m1), true);
	BOOST_REQUIRE_EQUAL(mr.create(m2), true);
	BOOST_REQUIRE_EQUAL(mr.create(m3), true);
	BOOST_TEST_MESSAGE(mr.getInfo());
	BOOST_REQUIRE_EQUAL(mr.getSize(), 3);
	BOOST_REQUIRE_EQUAL(mr.remove(m2), true);
	BOOST_REQUIRE_EQUAL(mr.getSize(), 2);
	BOOST_REQUIRE_EQUAL(mr.find("1"), m1);
	BOOST_REQUIRE_EQUAL(mr.getElement(0), m1);
	mr.clear();
	BOOST_REQUIRE_EQUAL(mr.getSize(), 0);
}
BOOST_AUTO_TEST_CASE(ShowtimeRepositoryCase)
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	boost::posix_time::time_duration td(120, 0, 0, 0);
	moviePtr m1(new Movie("1", "Terminator", 180, "Jakub Wawrzyniak", "akcji", 9.0));
	hallPtr h1(new Hall("1", "Kinder Bueno", 10, 10, true));
	showtimePtr sh1(new Showtime("1", LT + td, m1, h1, 20));
	showtimePtr sh2(new Showtime("2", LT + td, m1, h1, 22));
	showtimePtr sh3(new Showtime("3", LT + td + td, m1, h1, 24));
	ShowtimeRepository shr;
	BOOST_REQUIRE_EQUAL(shr.create(sh1), true);
	BOOST_REQUIRE_EQUAL(shr.create(sh2), true);
	BOOST_REQUIRE_EQUAL(shr.create(sh3), true);
	BOOST_TEST_MESSAGE(shr.getInfo());
	BOOST_REQUIRE_EQUAL(shr.getSize(), 3);
	BOOST_REQUIRE_EQUAL(shr.remove(sh2), true);
	BOOST_REQUIRE_EQUAL(shr.getSize(), 2);
	BOOST_REQUIRE_EQUAL(shr.find("1"), sh1);
	BOOST_REQUIRE_EQUAL(shr.getElement(0), sh1);
	BOOST_REQUIRE_EQUAL(shr.find("1"), sh1);
	BOOST_REQUIRE_EQUAL(shr.getSize(), 2);
	shr.clear();
	BOOST_REQUIRE_EQUAL(shr.getSize(), 0);
}
BOOST_AUTO_TEST_CASE(TicketRepositoryCase)
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	moviePtr m1(new Movie("1", "Terminator", 180, "Jakub Wawrzyniak", "akcji", 9.0));
	hallPtr h1(new Hall("1", "Kinder Bueno", 10, 10, true));
	showtimePtr sh1(new Showtime("1", LT, m1, h1, 20));
	clientPtr cl1(new Client("1", "Jan", "Nowak", 21, "jn@p.pl", "111222333"));
	ticketPtr t1(new Ticket(1, 2, sh1, cl1));
	ticketPtr t2(new Ticket(1, 3, sh1, cl1));
	ticketPtr t3(new Ticket(1, 4, sh1, cl1));
	TicketRepository tr;
	BOOST_REQUIRE_EQUAL(tr.create(t1), true);
	BOOST_REQUIRE_EQUAL(tr.create(t2), true);
	BOOST_REQUIRE_EQUAL(tr.create(t3), true);
	BOOST_TEST_MESSAGE(tr.getInfo());
	BOOST_REQUIRE_EQUAL(tr.getSize(), 3);
	BOOST_REQUIRE_EQUAL(tr.remove(t2), true);
	BOOST_REQUIRE_EQUAL(tr.getSize(), 2);
	BOOST_REQUIRE_EQUAL(tr.find(boost::lexical_cast<std::string>(t1->getId())), t1);
	BOOST_REQUIRE_EQUAL(tr.getElement(0), t1);
	tr.clear();
	BOOST_REQUIRE_EQUAL(tr.getSize(), 0);
}
BOOST_AUTO_TEST_CASE(HallRepositoryCase)
{
	hallPtr h1(new Hall("1", "Kinder Bueno", 10, 10, true));
	hallPtr h2(new Hall("2", "Pepsi", 9, 5, false));
	hallPtr h3(new Hall("3", "BMW", 15, 11, true));
	HallRepository hr;
	BOOST_REQUIRE_EQUAL(hr.create(h1), true);
	BOOST_REQUIRE_EQUAL(hr.create(h2), true);
	BOOST_REQUIRE_EQUAL(hr.create(h3), true);
	BOOST_TEST_MESSAGE(hr.getInfo());
	BOOST_REQUIRE_EQUAL(hr.getSize(), 3);
	BOOST_REQUIRE_EQUAL(hr.remove(h2), true);
	BOOST_REQUIRE_EQUAL(hr.getSize(), 2);
	BOOST_REQUIRE_EQUAL(hr.find("1"), h1);
	BOOST_REQUIRE_EQUAL(hr.getElement(0), h1);
	hr.clear();
	BOOST_REQUIRE_EQUAL(hr.getSize(), 0);
}

BOOST_AUTO_TEST_SUITE_END()