//
// Created by student on 30.12.2019.
//

#ifndef POBI_STUDENTTICKET_H
#define POBI_STUDENTTICKET_H
#include "TicketType.h"

class StudentTicket: public TicketType
{
public:
	StudentTicket();
	virtual ~StudentTicket();
	virtual double discount(double ticketPrice);
	virtual std::string getInfo();
};


#endif //POBI_STUDENTTICKET_H
