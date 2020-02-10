//
// Created by student on 30.12.2019.
//

#ifndef POBI_NORMALTICKET_H
#define POBI_NORMALTICKET_H
#include "TicketType.h"

class NormalTicket: public TicketType
{
public:
	NormalTicket();
	virtual ~NormalTicket();
	virtual double discount(double ticketPrice);
	virtual std::string getInfo();
};


#endif //POBI_NORMALTICKET_H
