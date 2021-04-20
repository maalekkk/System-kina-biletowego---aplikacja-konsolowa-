//
// Created by student on 30.12.2019.
//

#ifndef POBI_HALL_H
#define POBI_HALL_H
#include "Movie.h"
class Movie;

typedef std::shared_ptr<Movie> moviePtr;

class Hall
{
private:
	std::string id;
	std::string name;
	std::vector<moviePtr> movies;
	int rows;
	int seatsInRow;
	bool available3d;
public:
	Hall(const std::string &id, const std::string &name, int rows, int seatsInRow, bool available3D);
	virtual ~Hall();
	std::string getId() const;
	const std::string &getName() const;
	int getSize() const;
	int getAvailable3D() const;
	int getRows() const;
	int getSeatsInRow() const;
	int getNumberOfMovies() const;
	bool addMovie(const moviePtr &);
	bool removeMovie(const moviePtr &);
	std::string getInfo() const;
	std::string getMoviesInHallInfo() const;
	bool operator==(const Hall &rhs) const;
	bool operator!=(const Hall &rhs) const;
};

typedef std::shared_ptr<Hall> hallPtr;


#endif //POBI_HALL_H
