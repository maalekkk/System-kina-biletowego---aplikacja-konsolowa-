//
// Created by student on 30.12.2019.
//

#ifndef POBI_PREMIUMCLIENT_H
#define POBI_PREMIUMCLIENT_H
#include "ClientType.h"

class PremiumClient: public ClientType
{
public:
	PremiumClient();
	virtual ~PremiumClient();
	virtual double discount(double ticketPrice);
};


#endif //POBI_PREMIUMCLIENT_H
