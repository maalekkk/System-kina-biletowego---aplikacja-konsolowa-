//
// Created by student on 30.12.2019.
//

#include <Movie.h>
#include <sstream>
#include "ParameterException.h"

Movie::Movie(const std::string &id,
			 const std::string &title,
			 int duration,
			 const std::string &director,
			 const std::string &type,
			 double rating)
	: id(id), title(title), duration(duration), director(director), type(type), rating(rating)
{
	if (rating < 0 || rating > 10) {
		throw ParameterException("Ocena filmu musi sie miescic w przedziale 0-10");
	}

	if (duration < 0) {
		throw ParameterException("Dlugosc filmu musi byc dodatnia");
	}

	if (id.empty()) {
		throw ParameterException("Wymagane podanie id");
	}

	for (char i : director) {
		if (i < 65 || i > 122) {
			if (i != ' ') {
				throw ParameterException("Imie i nazwisko musi sie skladac z liter alfebetu bez polskich znakow");
			}
		}
	}

	if (title.empty()) {
		throw ParameterException("Wymagane podanie tytulu");
	}

	if (duration == 0) {
		throw ParameterException("Wymagane podanie dlugosci filmu");
	}

	if (director.empty()) {
		throw ParameterException("Wymagane podanie rezysera");
	}

	if (type.empty()) {
		throw ParameterException("Wymagane podanie rodzaju filmu");
	}

	bool temp = true;
	if (type == "akcji" || type == "romantyczny" || type == "dramat" || type == "horror" || type == "komedia"
		|| type == "psychologiczny" || type == "thriller" || type == "animowany" || type == "science fiction"
		|| type == "fantasy" || type == "dokumentalny" || type == "rodzinny") {
		temp = false;
	}
	if (temp) {
		throw ParameterException(
			"Rodzaj filmu musi byc jednym z tej lissty: akcji, romantyczny, dramat, horror, komedia, psychologiczny, thriller, animowany, science fiction, fantasy, dokumentalny, rodzinny");
	}
}

Movie::~Movie()
{

}

const std::string Movie::getInfo() const
{
	std::string info, sduration, srating;
	sduration = std::to_string(duration);
	srating = std::to_string(rating);
	info =
		"Film. ID: " + id + ", jego tytul to: " + title + ", trwa " + sduration + " minut, rezyserowal go " + director
			+ ". Jest to film typu " + type + " i srednia ocena filmu wynosi: " + srating;
	return info;
}

std::string Movie::getId() const
{
	return id;
}

const std::string &Movie::getTitle() const
{
	return title;
}

int Movie::getDuration() const
{
	return duration;
}

const std::string &Movie::getDirector() const
{
	return director;
}

const std::string &Movie::getType() const
{
	return type;
}

double Movie::getRating() const
{
	return rating;
}

bool Movie::addHall(const hallPtr &hall)
{
	for (const auto &it:this->halls) {
		if (it == hall) {
			return false;
		}
	}
	this->halls.push_back(hall);
	return true;
}

bool Movie::removeHall(const hallPtr &hall)
{
	for (int it = 0; it < int(halls.size()); it++) {
		if (halls[it] == hall) {
			halls.erase(halls.begin() + it);
			return true;
		}
	}
	return false;
}

int Movie::getNumberOfHalls() const
{
	return this->halls.size();
}
bool Movie::operator==(const Movie &rhs) const
{
	if (id != rhs.id ||
		title != rhs.title ||
		duration != rhs.duration ||
		director != rhs.director ||
		type != rhs.type ||
		rating != rhs.rating ||
		halls != rhs.halls) {
		return false;
	}
	int i = 0;
	for (const auto &it: halls) {
		if (it != rhs.halls[i]) {
			return false;
		}
		i++;
	}
	return true;
}
bool Movie::operator!=(const Movie &rhs) const
{
	return !(rhs == *this);
}
std::string Movie::getMoviesHallInfo() const
{
	{
		std::stringstream ss;
		ss << "Film grany jest na nastepujacych salach: \n";
		int i = 1;
		for (const auto &it: halls) {
			ss << i << ". " << it->getInfo() << "\n";
			i++;
		}
		return ss.str();
	}
}