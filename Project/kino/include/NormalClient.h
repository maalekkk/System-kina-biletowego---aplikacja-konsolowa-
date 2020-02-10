//
// Created by student on 30.12.2019.
//

#ifndef POBI_NORMALCLIENT_H
#define POBI_NORMALCLIENT_H
#include "ClientType.h"

class NormalClient: public ClientType
{
public:
	NormalClient();
	virtual ~NormalClient();
	virtual double discount(double ticketPrice);
};


#endif //POBI_NORMALCLIENT_H
