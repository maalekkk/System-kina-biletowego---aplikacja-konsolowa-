//
// Created by student on 30.12.2019.
//

#ifndef POBI_CLIENTMANAGER_H
#define POBI_CLIENTMANAGER_H
#include "ClientRepository.h"

class ClientManager
{
private:
	ClientRepository clients;
public:
	virtual ~ClientManager();
	ClientManager();
	bool createClient(const std::string &id,
					  const std::string &firstName,
					  const std::string &lastName,
					  int age,
					  const std::string &email,
					  const std::string &phoneNumber);
	bool createClient(clientPtr client);
	bool removeClient(clientPtr client);
	bool removeClient(std::string id);
	int countClients();
	std::string getClientsInfo();
	std::string getClientsTicketsInfo(std::string id);
	clientPtr operator()(std::string id);
};


#endif //POBI_CLIENTMANAGER_H
