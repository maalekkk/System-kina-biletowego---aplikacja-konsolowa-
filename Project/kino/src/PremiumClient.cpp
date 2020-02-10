//
// Created by student on 30.12.2019.
//

#include "PremiumClient.h"

PremiumClient::PremiumClient()
	: ClientType(4)
{}

PremiumClient::~PremiumClient()
{}

double PremiumClient::discount(double ticketPrice)
{
	return ticketPrice - 0.2 * ticketPrice;
}
