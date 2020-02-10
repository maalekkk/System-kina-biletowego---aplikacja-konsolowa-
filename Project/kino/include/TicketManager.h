//
// Created by student on 30.12.2019.
//

#ifndef POBI_TICKETMANAGER_H
#define POBI_TICKETMANAGER_H
#include "MovieRepository.h"
#include "ClientRepository.h"
#include "HallRepository.h"
#include "ShowtimeRepository.h"
#include "TicketRepository.h"

class Client;
class Movie;
class Hall;

typedef std::shared_ptr<Hall> hallPtr;

typedef std::shared_ptr<Movie> moviePtr;

typedef std::shared_ptr<Client> clientPtr;

class TicketManager
{
private:
	ShowtimeRepository showtimes;
	TicketRepository oldTickets;
	TicketRepository tickets;
public:
	TicketManager();
	virtual ~TicketManager();
	bool createTicket(const std::string &movieName,
					  const boost::local_time::local_date_time &time,
					  const clientPtr &client);
	bool createTicket(const moviePtr &movie, const boost::local_time::local_date_time &time, const clientPtr &client);
	bool createTicket(ticketPtr ticket);
	bool removeTicket(ticketPtr ticket);
	int countTickets();
	int countOldTickets();
	int countShowtimes();
	void create10Showtimes(std::vector<moviePtr> &movies, std::vector<hallPtr> &halls);
	bool createShowtime(const showtimePtr &showtime);
	void updateShowtimes();
	void updateTickets();
	showtimePtr getShowtimeFromID(const std::string &id);
	std::string getTicketsInfo();
	std::string getShowtimesInfo();
	ticketPtr operator()(const std::string &id);
};

#endif //POBI_TICKETMANAGER_H
