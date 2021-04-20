//
// Created by student on 30.12.2019.
//
#include "ClientManager.h"
#include <utility>

ClientManager::~ClientManager()
{

}

ClientManager::ClientManager()
{

}

bool
ClientManager::createClient(const std::string &id,
							const std::string &firstName,
							const std::string &lastName,
							int age,
							const std::string &email,
							const std::string &phoneNumber)
{
	return clients.create(clientPtr(new Client(id, firstName, lastName, age, email, phoneNumber)));
}

bool ClientManager::createClient(clientPtr client)
{
	return clients.create(std::move(client));
}

bool ClientManager::removeClient(clientPtr client)
{
	return clients.remove(std::move(client));
}

bool ClientManager::removeClient(std::string id)
{
	return clients.remove(clients.find(std::move(id)));
}

int ClientManager::countClients()
{
	return clients.getSize();
}

std::string ClientManager::getClientsInfo()
{
	return clients.getInfo();
}
clientPtr ClientManager::operator()(std::string id)
{
	return this->clients.find(std::move(id));
}
std::string ClientManager::getClientsTicketsInfo(std::string id)
{
	return clients.find(std::move(id))->getClientsTicketsInfo();
}