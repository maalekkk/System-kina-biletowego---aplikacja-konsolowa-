//
// Created by student on 30.12.2019.
//

#include "SeniorTicket.h"
SeniorTicket::SeniorTicket()
{

}
SeniorTicket::~SeniorTicket()
{

}
double SeniorTicket::discount(double ticketPrice)
{
	return ticketPrice - 0.34 * ticketPrice;
}
std::string SeniorTicket::getInfo()
{
	return TicketType::getInfo() + "dla seniora.";
}
