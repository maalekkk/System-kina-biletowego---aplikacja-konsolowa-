//
// Created by student on 30.12.2019.
//

#include "NormalClient.h"

NormalClient::NormalClient()
	: ClientType(1)
{

}

NormalClient::~NormalClient()
{

}

double NormalClient::discount(double ticketPrice)
{
	return ticketPrice;
}