//
// Created by student on 30.12.2019.
//

#include "Ticket.h"
#include "StudentTicket.h"
#include "NormalTicket.h"
#include "SeniorTicket.h"
#include "ParameterException.h"

Ticket::Ticket(int row, int seat, const showtimePtr &showtime, const clientPtr &client)
	: row(row), seat(seat),
	  showtime(showtime),
	  client(client)
{
	if (client->getAge() < 27) {
		this->ticketType = ticketTypePtr(new StudentTicket());
	}
	else if (client->getAge() > 66) {
		this->ticketType = ticketTypePtr(new SeniorTicket());
	}
	else {
		this->ticketType = ticketTypePtr(new NormalTicket());
	}
	client->setType(client->getThisMonthTicketsSize());
	this->price = this->client->getClientType()->discount(this->ticketType->discount(this->showtime->getPrice()));

	if (this->showtime == nullptr) {
		throw ParameterException("Wymagane podanie seansu");
	}

	if (client == nullptr) {
		throw ParameterException("Wymagane podanie clienta");
	}

	if (row < 1) {
		throw ParameterException("Rzad musi byc dodatni");
	}

	if (seat < 1) {
		throw ParameterException("Siedzenie musi byc dodatnie");
	}
	if (seat > 100) {
		throw ParameterException("Numer Siedzenia musi byc mniejszy");
	}

	if (row > 100) {
		throw ParameterException("Numer rzedu musi byc mniejszy");
	}
}

Ticket::~Ticket()
{

}

const boost::uuids::uuid Ticket::getId() const
{
	return id;
}

int Ticket::getPrice() const
{
	return price;
}

int Ticket::getRow() const
{
	return row;
}

int Ticket::getSeat() const
{
	return seat;
}

const LTime &Ticket::getBuyTime() const
{
	return buyTime;
}

const showtimePtr &Ticket::getShowtime() const
{
	return showtime;
}

const clientPtr &Ticket::getClient() const
{
	return client;
}

const ticketTypePtr &Ticket::getTicketType() const
{
	return ticketType;
}

const std::string Ticket::getInfo() const
{
	std::stringstream info;
	info << "Bilet, ID: " << this->getId() << ", rzad: " << this->row << ", siedzenie: " << this->seat << ". "
		 << this->ticketType->getInfo() << "\nPokaz filmowy o ID:" << this->showtime->getId()
		 << ". Czas rozpoczecia to: " << this->showtime->getShowtimeStart() << ". Cena biletu to: " << this->price
		 << ".\n" << this->showtime->getMovie()->getInfo() << "\nFilm grany jest na sali: "
		 << this->showtime->getHall()->getName() << ", o ID: " << this->showtime->getHall()->getId()
		 << ".\nKlient kupujacy: " << this->client->getId() << ", imie i nazwisko: " << this->client->getFirstName()
		 << " " << this->client->getLastName() << ".";
	return info.str();
}

void Ticket::setPrice(int ticketPrice)
{
	Ticket::price = ticketPrice;
}

bool Ticket::operator==(const Ticket &rhs) const
{
	return id == rhs.id &&
		price == rhs.price &&
		row == rhs.row &&
		seat == rhs.seat &&
		buyTime == rhs.buyTime &&
		showtime == rhs.showtime &&
		client == rhs.client;
}

bool Ticket::operator!=(const Ticket &rhs) const
{
	return !(rhs == *this);
}