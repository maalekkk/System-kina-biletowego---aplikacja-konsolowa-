//
// Created by Bartek on 15.12.2019.
//
#include "Client.h"
#include "NormalClient.h"
#include "PremiumClient.h"
#include "ParameterException.h"
#include "AvaliableException.h"

Client::Client(const std::string &id,
			   const std::string &firstName,
			   const std::string &lastName,
			   int age,
			   const std::string &email,
			   const std::string &phoneNumber)
	: id(id), firstName(firstName), lastName(lastName), age(age), email(email),
	  phoneNumber(phoneNumber), clientType(new NormalClient())
{
	if (id.empty()) {
		throw ParameterException("Wymagane podanie id");
	}
	if (firstName.empty()) {
		throw ParameterException("Wymagane podanie imienia");
	}
	if (lastName.empty()) {
		throw ParameterException("Wymagane podanie nazwiska");
	}
	if (email.empty()) {
		throw ParameterException("Wymagane podanie emaila");
	}
	if (phoneNumber.empty()) {
		throw ParameterException("Wymagane podanie numeru telefonu");
	}
	if (age < 0) {
		throw ParameterException("Wiek musi byc nie ujemny");
	}
	if (phoneNumber.length() != 9) {
		throw ParameterException("Numer telefonu musi miec 9 cyfr");
	}
	if (age > 120) {
		throw ParameterException("Wiek musi byc realistyczny");
	}

	for (int i = 0; i < int(firstName.size()); i++) {
		if (firstName[i] < 65 || firstName[i] > 122) {
			throw ParameterException("Imie i nazwisko musi sie skladac z liter alfebetu bez polskich znakow");
		}
	}

	for (int i = 0; i < int(lastName.size()); i++) {
		if (lastName[i] < 65 || lastName[i] > 122) {
			throw ParameterException("Imie i nazwisko musi sie skladac z liter alfebetu bez polskich znakow");
		}
	}

}

Client::~Client()
{

}

std::string Client::getId()
{
	return id;
}

const std::string &Client::getFirstName() const
{
	return firstName;
}

const std::string &Client::getLastName() const
{
	return lastName;
}

int Client::getAge() const
{
	return age;
}

const std::string &Client::getEmail() const
{
	return email;
}

const std::string &Client::getPhoneNumber() const
{
	return phoneNumber;
}

const clientTypePtr &Client::getClientType() const
{
	return clientType;
}

void Client::addTicket(ticketPtr ticket)
{
	this->tickets.push_back(ticket);
}

void Client::removeTicket(ticketPtr ticket)
{
	for (int it = 0; it < int(tickets.size()); it++) {
		if (tickets[it] == ticket) {
			tickets.erase(tickets.begin() + it);
		}
	}
}

std::string Client::getInfo() const
{
	std::string sage;
	sage = std::to_string(age);
	return "Klient o ID: " + id + ", ma na imie " + firstName + ", na nazwisko " + lastName + ", ma " + sage
		+ " lat. Jego email to: " + email + ", a numer telefonu to: " + phoneNumber + ".";
}

int Client::getTicketsSize() const
{
	return this->tickets.size();
}

int Client::getThisMonthTicketsSize() const
{
	int monthTickets = 0;
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime now = boost::local_time::local_sec_clock::local_time(timeZone);
	for (const auto &it: tickets) {
		if (it->getShowtime()->getShowtimeStart().date().month() == now.date().month()) {
			monthTickets++;
		}
	}
	return monthTickets;
}

void Client::setType(int numberOfTickets)
{
	switch (numberOfTickets) {
		case 0:
		case 1:
		case 2:
		case 3:this->clientType = clientTypePtr(new NormalClient());
			break;
		default:this->clientType = clientTypePtr(new PremiumClient());
			break;
	}
}
bool Client::operator==(const Client &rhs) const
{
	if (id != rhs.id || firstName != rhs.firstName || lastName != rhs.lastName || age != rhs.age || email != rhs.email
		|| phoneNumber != rhs.phoneNumber) {
		return false;
	}
	int i = 0;
	for (const auto &it: tickets) {
		if (it != rhs.tickets[i]) {
			return false;
		}
		i++;
	}
	return true;
}
bool Client::operator!=(const Client &rhs) const
{
	return !(rhs == *this);
}
std::string Client::getClientsTicketsInfo() const
{
	std::string s = "Informacje o biletach klienta o ID: " + this->id + "\n";
	for (auto it: tickets) {
		s += it->getInfo() + "\n";
	}
	return s;
}
ticketPtr Client::getTicket(moviePtr movie, LTime showtimeStart)
{
	bool flag = false;
	ticketPtr temp = nullptr;
	for (const auto &it: tickets) {
		if (it->getShowtime()->getMovie() == movie
			&& it->getShowtime()->getShowtimeStart().date() >= showtimeStart.date()) {
			if (!flag) {
				temp = it;
				flag = true;
			}
			if (temp->getShowtime()->getShowtimeStart() > it->getShowtime()->getShowtimeStart()) {
				temp = it;
			}
		}
	}
	if (temp != nullptr) {
		return temp;
	}
	else {
		throw AvaliableException("Klient nie posiada takiego biletu");
	}
}