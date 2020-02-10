//
// Created by Bartek on 15.12.2019.
//

#ifndef POBI_CLIENT_H
#define POBI_CLIENT_H
#include "Ticket.h"
#include "ClientType.h"
class Ticket;
class ClientType;

typedef std::shared_ptr<Ticket> ticketPtr;

typedef std::shared_ptr<ClientType> clientTypePtr;

class Client
{
private:
	std::string id;
	std::string firstName;
	std::string lastName;
	int age;
	std::string email;
	std::string phoneNumber;
	clientTypePtr clientType;
	std::vector<ticketPtr> tickets;
public:
	Client(const std::string &id,
		   const std::string &firstName,
		   const std::string &lastName,
		   int age,
		   const std::string &email,
		   const std::string &phoneNumber);
	virtual ~Client();
	std::string getId();
	const std::string &getFirstName() const;
	const std::string &getLastName() const;
	int getAge() const;
	const std::string &getEmail() const;
	const std::string &getPhoneNumber() const;
	const clientTypePtr &getClientType() const;
	int getTicketsSize() const;
	int getThisMonthTicketsSize() const;
	void setType(int numberOfTickets);
	void addTicket(ticketPtr);
	void removeTicket(ticketPtr);
	ticketPtr getTicket(moviePtr movie, LTime showtimeStart);

	std::string getInfo() const;
	std::string getClientsTicketsInfo() const;
	bool operator==(const Client &rhs) const;
	bool operator!=(const Client &rhs) const;
};

typedef std::shared_ptr<Client> clientPtr;

#endif //POBI_CLIENT_H
