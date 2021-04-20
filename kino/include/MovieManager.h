//
// Created by student on 30.12.2019.
//

#ifndef POBI_MOVIEMANAGER_H
#define POBI_MOVIEMANAGER_H
#include "MovieRepository.h"

class MovieManager
{
private:
	MovieRepository movies;
public:
	virtual ~MovieManager();
	MovieManager();
	bool createMovie(std::string id,
					 std::string title,
					 int duration,
					 std::string director,
					 std::string type,
					 double rating);
	bool createMovie(moviePtr);
	bool removeMovie(moviePtr);
	bool removeMovie(std::string id);
	bool addHallToMovie(std::string id, hallPtr);
	std::string getMoviesInfo();
	std::string getMoviesHallInfo(std::string movieId);
	const std::vector<moviePtr> &getElements() const;
	int countMovies();
	moviePtr operator()(std::string id);
};
#endif //POBI_MOVIEMANAGER_H
