//
// Created by student on 30.12.2019.
//

#ifndef POBI_SENIORTICKET_H
#define POBI_SENIORTICKET_H
#include "TicketType.h"

class SeniorTicket: public TicketType
{
public:
	SeniorTicket();
	virtual ~SeniorTicket();
	virtual double discount(double ticketPrice);
	virtual std::string getInfo();
};


#endif //POBI_SENIORTICKET_H
