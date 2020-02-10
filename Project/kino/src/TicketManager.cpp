//
// Created by student on 30.12.2019.
//

#include "TicketManager.h"
#include "DuplicateException.h"
#include <random>
#include <utility>

TicketManager::TicketManager()
{

}

TicketManager::~TicketManager()
{

}

bool TicketManager::createTicket(const std::string &movieName,
								 const boost::local_time::local_date_time &time,
								 const clientPtr &client)
{
	showtimePtr showtime = showtimes.findWithMovie(movieName, time);
	for (const auto &it: tickets.getElements()) {
		if (it->getClient() == client && it->getShowtime() == showtime) {
			throw DuplicateException("Klient posiada juz bilet na ten film");
		}
	}
	ticketPtr
		ticket(new Ticket(showtime->getFreeRow(), showtime->getFreeSeat(showtime->getFreeRow()), showtime, client));
	client->addTicket(ticket);
	return this->tickets.create(ticket);
}

bool TicketManager::createTicket(const moviePtr &movie,
								 const boost::local_time::local_date_time &time,
								 const clientPtr &client)
{
	showtimePtr showtime = showtimes.findWithMovie(movie, time);
	return this->tickets.create(ticketPtr(new Ticket(showtime->getFreeRow(),
													 showtime->getFreeSeat(showtime->getFreeRow()),
													 showtime,
													 client)));
}

bool TicketManager::createTicket(ticketPtr ticket)
{
	return tickets.create(std::move(ticket));
}

bool TicketManager::removeTicket(ticketPtr ticket)
{
	return tickets.remove(std::move(ticket));
}

void TicketManager::updateShowtimes()
{
	showtimes.update();
}

void TicketManager::updateTickets()
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	std::vector actual(tickets.getElements());
	for (int i = 0; i < int(tickets.getElements().size()); i++) {
		boost::posix_time::time_duration td(0, actual[i]->getShowtime()->getMovie()->getDuration(), 0, 0);
		if ((actual[i]->getShowtime()->getShowtimeStart() + td).date() < LT.date()) {
			tickets.remove(tickets.getElements()[i]);
			oldTickets.create(actual[i]);
		}
	}
}

std::string TicketManager::getTicketsInfo()
{

	return tickets.getInfo();
}

std::string TicketManager::getShowtimesInfo()
{
	return showtimes.getInfo();
}

int TicketManager::countTickets()
{
	return this->tickets.getSize();
}

int TicketManager::countOldTickets()
{
	return this->oldTickets.getSize();
}

void TicketManager::create10Showtimes(std::vector<moviePtr> &movies, std::vector<hallPtr> &halls)
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	boost::posix_time::time_duration td(0, LT.time_of_day().minutes(), LT.time_of_day().seconds(), 0);
	LT = LT - td;
	int index = showtimes.getActualId();
	for (int i = index + 1; i <= index + 10; i++) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<> r1(1, 168);
		std::uniform_int_distribution<> r2(0, 59);
		std::uniform_int_distribution<> r3(10, 30);
		int hour = r1(mt);
		int min = r2(mt);
		int price = r3(mt);
		boost::posix_time::time_duration time_duration(hour, (min / 15) * 15, 0, 0);
		int extraHours = 0;
		if ((LT + time_duration).time_of_day().hours() < 9 || (LT + time_duration).time_of_day().hours() > 22) {
			extraHours = 10;
		}
		boost::posix_time::time_duration time_durationExtra(extraHours, 0, 0, 0);
		std::uniform_int_distribution<> r4(0, movies.size() - 1);
		std::uniform_int_distribution<> r5(0, halls.size() - 1);
		int movieIndex = r4(mt);
		int hallsIndex = r5(mt);
		showtimes.create(showtimePtr(new Showtime(std::to_string(i),
												  LT + time_duration + time_durationExtra,
												  movies[movieIndex],
												  halls[hallsIndex],
												  price)));
	}
}

ticketPtr TicketManager::operator()(const std::string &id)
{
	if (this->tickets.find(id) != nullptr) {
		return this->tickets.find(id);
	}
	if (this->oldTickets.find(id) != nullptr) {
		return this->oldTickets.find(id);
	}
	return nullptr;
}

int TicketManager::countShowtimes()
{
	return showtimes.getSize();
}

bool TicketManager::createShowtime(const showtimePtr &showtime)
{
	return showtimes.create(showtime);
}

showtimePtr TicketManager::getShowtimeFromID(const std::string &id)
{
	return showtimes.find(id);
}