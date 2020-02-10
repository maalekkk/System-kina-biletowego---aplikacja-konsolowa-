//
// Created by student on 30.12.2019.
//

#ifndef POBI_CLIENTTYPE_H
#define POBI_CLIENTTYPE_H
#include <string>
#include <memory>

class ClientType
{
private:
	int movieCount = 1;
public:
	ClientType(int movieCount);
	virtual ~ClientType();
	virtual double discount(double ticketPrice) = 0;
	int getMovieCount();
};

typedef std::shared_ptr<ClientType> clientTypePtr;


#endif //POBI_CLIENTTYPE_H
