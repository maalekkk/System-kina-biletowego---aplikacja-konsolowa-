//
// Created by student on 30.12.2019.
//

#ifndef POBI_TICKET_H
#define POBI_TICKET_H
#include "Showtime.h"
#include "Client.h"
#include "TicketType.h"
class Client;
class TicketType;

typedef std::shared_ptr<Client> clientPtr;

typedef std::shared_ptr<TicketType> ticketTypePtr;

class Ticket
{
private:
	boost::uuids::uuid id = boost::uuids::random_generator()();
	int price;
	int row;
	int seat;
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime buyTime = boost::local_time::local_sec_clock::local_time(timeZone);
	showtimePtr showtime;
	clientPtr client;
	ticketTypePtr ticketType;
public:
	Ticket(int row, int seat, const showtimePtr &showtime, const clientPtr &client);
	virtual ~Ticket();

	const boost::uuids::uuid getId() const;
	int getPrice() const;
	int getRow() const;
	int getSeat() const;
	const LTime &getBuyTime() const;
	const showtimePtr &getShowtime() const;
	const clientPtr &getClient() const;
	const ticketTypePtr &getTicketType() const;
	const std::string getInfo() const;
	void setPrice(int ticketPrice);
	bool operator==(const Ticket &rhs) const;
	bool operator!=(const Ticket &rhs) const;
};

typedef std::shared_ptr<Ticket> ticketPtr;

#endif //POBI_TICKET_H
