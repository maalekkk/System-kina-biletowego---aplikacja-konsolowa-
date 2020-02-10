//
// Created by student on 30.12.2019.
//

#include "NormalTicket.h"
NormalTicket::NormalTicket()
{}

NormalTicket::~NormalTicket()
{}

double NormalTicket::discount(double ticketPrice)
{
	return ticketPrice;
}
std::string NormalTicket::getInfo()
{
	return TicketType::getInfo() + "normalny.";
}
