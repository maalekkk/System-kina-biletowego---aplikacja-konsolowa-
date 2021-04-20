//
// Created by student on 30.12.2019.
//

#ifndef POBI_MOVIE_H
#define POBI_MOVIE_H
#include <memory>
#include <vector>
#include "Hall.h"
class Hall;

typedef std::shared_ptr<Hall> hallPtr;

class Movie
{
private:
	std::string id;
	std::string title;
	int duration;
	std::string director;
	std::string type;
	double rating;
	std::vector<hallPtr> halls;
public:
	Movie(const std::string &id,
		  const std::string &title,
		  int duration,
		  const std::string &director,
		  const std::string &type,
		  double rating);
	virtual ~Movie();
	std::string getId() const;
	const std::string &getTitle() const;
	int getDuration() const;
	const std::string &getDirector() const;
	const std::string &getType() const;
	double getRating() const;
	bool addHall(const hallPtr &hall);
	bool removeHall(const hallPtr &hall);
	int getNumberOfHalls() const;
	const std::string getInfo() const;
	std::string getMoviesHallInfo() const;
	bool operator==(const Movie &rhs) const;
	bool operator!=(const Movie &rhs) const;
};

typedef std::shared_ptr<Movie> moviePtr;

#endif //POBI_MOVIE_H
