//
// Created by student on 30.12.2019.
//

#ifndef POBI_SHOWTIME_H
#define POBI_SHOWTIME_H
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include "Hall.h"
#include "Movie.h"

typedef boost::local_time::local_date_time LTime;

typedef boost::local_time::time_zone_ptr TZone;

class Showtime
{
private:
	std::string id;
	TZone timeZone{new boost::local_time::posix_time_zone("CET+1")};
	LTime showtimeStart;
	moviePtr movie;
	hallPtr hall;
	int price;
	int numberOfSeats;
	bool **freeSeats;
public:
	Showtime(const std::string &id, const LTime &showtimeStart, const moviePtr &movie, const hallPtr &hall, int price);
	virtual ~Showtime();
	std::string getId() const;
	const LTime &getShowtimeStart() const;
	int getNumberOfSeats() const;
	int getPrice() const;
	const hallPtr &getHall() const;
	const moviePtr &getMovie() const;
	int getFreeRow() const;
	int getFreeSeat(int row) const;
	std::string getInfo() const;
	bool operator==(const Showtime &rhs) const;
	bool operator!=(const Showtime &rhs) const;
};

typedef std::shared_ptr<Showtime> showtimePtr;

#endif //POBI_SHOWTIME_H
