//
// Created by student on 30.12.2019.
//

#include "MovieManager.h"
MovieManager::~MovieManager()
{

}

MovieManager::MovieManager()
{

}

bool MovieManager::createMovie(std::string id,
							   std::string title,
							   int duration,
							   std::string director,
							   std::string type,
							   double rating)
{
	return movies.create(moviePtr(new Movie(id, title, duration, director, type, rating)));
}

bool MovieManager::createMovie(moviePtr movie)
{
	return movies.create(movie);
}

bool MovieManager::removeMovie(moviePtr movie)
{
	return movies.remove(movie);
}

bool MovieManager::removeMovie(std::string id)
{
	return movies.remove(movies.find(id));
}

bool MovieManager::addHallToMovie(std::string id, hallPtr hall)
{
	return movies.find(id)->addHall(hall);;
}

std::string MovieManager::getMoviesInfo()
{
	return movies.getInfo();
}

int MovieManager::countMovies()
{
	return movies.getSize();
}

moviePtr MovieManager::operator()(std::string id)
{
	return this->movies.find(id);
}

std::string MovieManager::getMoviesHallInfo(std::string movieId)
{
	return movies.find(movieId)->getMoviesHallInfo();
}

const std::vector<moviePtr> &MovieManager::getElements() const
{
	return movies.getElements();
}