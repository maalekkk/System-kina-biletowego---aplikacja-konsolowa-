//
// Created by student on 30.12.2019.
//

#include "HallManager.h"
#include <utility>

HallManager::~HallManager()
{

}

HallManager::HallManager()
{

}

bool HallManager::createHall(const std::string &id, const std::string &name, int rows, int seatsInRow, bool available3d)
{
	return halls.create(hallPtr(new Hall(id, name, rows, seatsInRow, available3d)));
}

bool HallManager::createHall(hallPtr hall)
{
	return halls.create(std::move(hall));
}

bool HallManager::removeHall(std::string id)
{
	return halls.remove(halls.find(std::move(id)));
}

bool HallManager::removeHall(hallPtr hall)
{
	return halls.remove(std::move(hall));
}

bool HallManager::addMovieToHall(std::string id, const moviePtr &movie)
{
	return halls.find(std::move(id))->addMovie(movie);
}

std::string HallManager::getHallsInfo()
{
	return halls.getInfo();
}

int HallManager::countHall()
{
	return halls.getSize();
}

hallPtr HallManager::operator()(std::string id)
{
	return this->halls.find(std::move(id));
}

std::string HallManager::getMoviesInHallInfo(std::string hallId)
{
	return halls.find(std::move(hallId))->getMoviesInHallInfo();
}

const std::vector<hallPtr> &HallManager::getElements() const
{
	return halls.getElements();
}