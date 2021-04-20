//
// Created by student on 30.12.2019.
//

#include <sstream>
#include "Hall.h"
#include "ParameterException.h"

Hall::Hall(const std::string &id, const std::string &name, int rows, int seatsInRow, bool available3D)
	: id(id), name(name), rows(rows), seatsInRow(seatsInRow), available3d(available3D)
{
	if (rows < 0) {
		throw ParameterException("Liczba rzedow musi byc nie ujemna");
	}

	if (seatsInRow < 0) {
		throw ParameterException("Liczba siedzen musi byc nie ujemna");
	}

	if (name.empty()) {
		throw ParameterException("Wymagane podanie imienia");
	}

	if (id.empty()) {
		throw ParameterException("Wymagane podanie id");
	}

	if (rows == 0) {
		throw ParameterException("Wymagane podanie liczby rzedow");
	}

	if (seatsInRow > 100) {
		throw ParameterException("Nie moze byc tyle siedzen");
	}

	if (rows > 100) {
		throw ParameterException("Nie moze byc tyle rzedow");
	}
}

Hall::~Hall()
{

}

std::string Hall::getId() const
{
	return id;
}

const std::string &Hall::getName() const
{
	return name;
}

int Hall::getSize() const
{
	return this->seatsInRow * this->rows;
}

int Hall::getAvailable3D() const
{
	return available3d;
}

int Hall::getRows() const
{
	return rows;
}

int Hall::getSeatsInRow() const
{
	return seatsInRow;
}

std::string Hall::getInfo() const
{
	std::string info, srows, sseats, s3d;
	srows = std::to_string(rows);
	sseats = std::to_string(seatsInRow);
	if (!available3d) {
		s3d = "nie wyswietla filmow";
	}
	else {
		s3d = "wyswietla filmy";
	}
	info = "Sala o ID: " + id + ", nazywa sie " + name + ", ma " + srows + " rzedow i w nich znajduje sie po " + sseats
		+ " siedzen. Sala " + s3d + " 3D";
	return info;
}

int Hall::getNumberOfMovies() const
{
	return this->movies.size();
}

bool Hall::addMovie(const moviePtr& movie)
{
	for (const auto &it: this->movies) {
		if (it == movie) {
			return false;
		}
	}
	this->movies.push_back(movie);
	return true;
}

bool Hall::removeMovie(const moviePtr& movie)
{
	for (int it = 0; it < int(movies.size()); it++) {
		if (movies[it] == movie) {
			movies.erase(movies.begin() + it);
			return true;
		}
	}
	return false;
}

bool Hall::operator==(const Hall &rhs) const
{
	if (id != rhs.id || name != rhs.name || available3d != rhs.available3d || movies != rhs.movies || rows != rhs.rows
		|| seatsInRow != rhs.seatsInRow) {
		return false;
	}
	int i = 0;
	for (const auto &it: movies) {
		if (it != rhs.movies[i]) {
			return false;
		}
		i++;
	}
	return true;
}

bool Hall::operator!=(const Hall &rhs) const
{
	return !(rhs == *this);
}

std::string Hall::getMoviesInHallInfo() const
{
	std::stringstream ss;
	ss << "Filmy grane na danej sali: \n";
	int i = 1;
	for (const auto &it: movies) {
		ss << i << ". " << it->getInfo() << "\n";
		i++;
	}
	return ss.str();
}