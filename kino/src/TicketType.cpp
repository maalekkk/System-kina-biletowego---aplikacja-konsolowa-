//
// Created by student on 30.12.2019.
//

#include "TicketType.h"
TicketType::TicketType()
{}

TicketType::~TicketType()
{}

std::string TicketType::getInfo()
{
	return "Jest to bilet ";
}
int TicketType::getAge() const
{
	return age;
}
