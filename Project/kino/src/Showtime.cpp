//
// Created by student on 30.12.2019.
//

#include "Showtime.h"
#include "ParameterException.h"
#include "AvaliableException.h"

Showtime::Showtime(const std::string &id,
				   const LTime &showtimeStart,
				   const moviePtr &movie,
				   const hallPtr &hall,
				   int price)
	: id(id), showtimeStart(showtimeStart), movie(movie), hall(hall), price(price)
{
	this->freeSeats = new bool *[hall->getRows()];
	for (int i = 1; i <= hall->getRows(); i++) {
		this->freeSeats[i] = new bool[hall->getSeatsInRow() + 1];
	}
	//czyszczenie tablicy (wszystkie miejsca wolne)
	for (int i = hall->getRows(); i > 0; i--) {
		for (int j = hall->getSeatsInRow(); j > 0; j--) {
			freeSeats[i][j] = false;
		}
	}

	LTime LT2 = boost::local_time::local_sec_clock::local_time(timeZone);
	if (showtimeStart.date() < LT2.date()) {
		throw ParameterException("Data seansu musi byc pozniejsza niz w chwili obecnej");
	}

	if (price < 0) {
		throw ParameterException("Cena musi byc nie ujemna");
	}

	if (id.empty()) {
		throw ParameterException("Wymagane podanie id");
	}

	if (showtimeStart.is_not_a_date_time()) {
		throw ParameterException("Wymagane podanie daty");
	}

	if (hall == nullptr) {
		throw ParameterException("Wymagane podanie sali");
	}

	if (movie == nullptr) {
		throw ParameterException("Wymagane podanie filmu");
	}
}

Showtime::~Showtime()
{

}

std::string Showtime::getId() const
{
	return id;
}

const LTime &Showtime::getShowtimeStart() const
{
	return showtimeStart;
}

int Showtime::getNumberOfSeats() const
{
	int seats = this->hall->getSize();
	for (int i = hall->getRows(); i > 0; i--) {
		bool end = false;
		for (int j = hall->getSeatsInRow(); j > 0; j--) {
			if (freeSeats[i][j]) {
				seats = seats - 1;
			}
			else {
				end = true;
				break;
			}
		}
		if (end) {
			break;
		}
	}
	return seats;
}

int Showtime::getPrice() const
{
	return price;
}

const hallPtr &Showtime::getHall() const
{
	return hall;
}

const moviePtr &Showtime::getMovie() const
{
	return movie;
}

int Showtime::getFreeRow() const
{
	if (this->getNumberOfSeats() != 0) {
		for (int i = hall->getRows(); i > 0; i--) {
			for (int j = hall->getSeatsInRow(); j > 0; j--) {
				if (freeSeats[i][j] == 0) {
					return i;
				}
			}
		}
	}
	throw AvaliableException("Brak wolnego rzedu");
}

int Showtime::getFreeSeat(int row) const
{
	for (int j = hall->getSeatsInRow(); j > 0; j--) {
		if (freeSeats[row][j] == 0) {
			freeSeats[row][j] = 1;
			return j;
		}
	}
	throw AvaliableException("Brak wolnego miejsca");
}

std::string Showtime::getInfo() const
{
	std::stringstream info;
	info << "Pokaz filmowy, ID: " << this->id;
	info << ". Czas zaczecia to: " << this->showtimeStart;
	std::string sprice = std::to_string(this->price);
	info << ", cena biletu to: " << sprice;
	info << ".\nInformacja o sali: " << this->hall->getInfo();
	info << ".\nInformacja o filmie: " << this->movie->getInfo();
	return info.str();
}
bool Showtime::operator==(const Showtime &rhs) const
{
	return id == rhs.id &&
		timeZone == rhs.timeZone &&
		showtimeStart == rhs.showtimeStart &&
		numberOfSeats == rhs.numberOfSeats &&
		price == rhs.price &&
		freeSeats == rhs.freeSeats &&
		hall == rhs.hall &&
		movie == rhs.movie;
}
bool Showtime::operator!=(const Showtime &rhs) const
{
	return !(rhs == *this);
}

