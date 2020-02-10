//
// Created by student on 30.12.2019.
//

#ifndef POBI_TICKETTYPE_H
#define POBI_TICKETTYPE_H
#include <string>

class TicketType
{
private:
	int age;
public:
	int getAge() const;
	TicketType();
	virtual ~TicketType();
	virtual double discount(double ticketPrice) = 0;
	virtual std::string getInfo();
};


#endif //POBI_TICKETTYPE_H
