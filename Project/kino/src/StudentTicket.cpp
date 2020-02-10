//
// Created by student on 30.12.2019.
//

#include "StudentTicket.h"
StudentTicket::StudentTicket()
{}

StudentTicket::~StudentTicket()
{}

double StudentTicket::discount(double ticketPrice)
{
	return ticketPrice - 8;
}

std::string StudentTicket::getInfo()
{
	return TicketType::getInfo() + "studencki.";
}
