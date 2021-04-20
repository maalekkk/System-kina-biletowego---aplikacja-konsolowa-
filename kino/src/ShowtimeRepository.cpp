//
// Created by student on 30.12.2019.
//

#include "ShowtimeRepository.h"
#include "AvaliableException.h"
#include "DuplicateException.h"

typedef std::shared_ptr<Movie> moviePtr;

bool ShowtimeRepository::create(const showtimePtr &element)
{
	for (const auto &it: elements) {
		if (it == element) {
			throw DuplicateException("Juz istnieje dany seans w naszej bazie");
		}
	}
	elements.push_back(element);
	return true;
}

bool ShowtimeRepository::remove(const showtimePtr &element)
{
	for (int i = 0; i < int(elements.size()); i++) {
		if (elements[i] == element) {
			elements.erase(elements.begin() + i);
			return true;
		}
	}
	return false;
}

void ShowtimeRepository::clear()
{
	elements.clear();
}

showtimePtr ShowtimeRepository::find(const std::string &id)
{
	for (auto it: elements) {
		if (boost::lexical_cast<std::string>(it->getId()) == id) {
			return it;
		}
	}
	throw AvaliableException("Brak seansu o podanym ID.");
}

showtimePtr ShowtimeRepository::getElement(int i)
{
	if (i <= int(elements.size())) {
        return elements[i];
    }
	else {
        throw AvaliableException("W naszej bazie nie istnieje tyle seansow");
    }
}

std::string ShowtimeRepository::getInfo()
{
	std::stringstream ss;
	ss << "Informacje o repozytorium: \n";
	for (auto it: elements) {
		ss << it->getInfo() << "\n\n";
	}
	return ss.str();
}

int ShowtimeRepository::getSize()
{
	return elements.size();
}

void ShowtimeRepository::update()
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	std::vector temp(elements);
	for (int i = 0; i < int(this->elements.size()); i++) {
		if (temp[i]->getShowtimeStart().date() < LT.date()) {
            elements.erase(elements.begin() + i);
        }
	}
}

showtimePtr ShowtimeRepository::findWithMovie(const moviePtr &movie, const LTime &time)
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	showtimePtr temp = nullptr;
	bool flag = false;
	for (const auto &it: elements) {
		if (it->getMovie() == movie && it->getShowtimeStart() >= time) {
			if (!flag) {
				temp = it;
				flag = true;
			}
			if (temp->getShowtimeStart() > it->getShowtimeStart()) {
				temp = it;
			}
		}
	}
	if (temp != nullptr) {
		return temp;
	}
	else {
		throw AvaliableException("Film o podanej nazwie nie jest obecnie grany w naszym kinie");
	}
}
showtimePtr ShowtimeRepository::findWithMovie(const std::string &movieTitle, const LTime &time)
{
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime LT = boost::local_time::local_sec_clock::local_time(timeZone);
	showtimePtr temp = nullptr;
	bool flag = false;
	for (const auto &it: elements) {
		if (it->getMovie()->getTitle() == movieTitle && it->getShowtimeStart() >= time) {
			if (!flag) {
				temp = it;
				flag = true;
			}
			if (temp->getShowtimeStart() > it->getShowtimeStart()) {
				temp = it;
			}
		}
	}
	if (temp != nullptr) {
		return temp;
	}
	else {
		throw AvaliableException("Film o podanej nazwie nie jest obecnie grany w naszym kinie");
	}
}
int ShowtimeRepository::getActualId()
{
	if (elements.empty()) {
		return 0;
	}
	return std::stoi(elements.back()->getId());
}