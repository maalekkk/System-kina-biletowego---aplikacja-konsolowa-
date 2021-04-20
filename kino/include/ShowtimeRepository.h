//
// Created by student on 30.12.2019.
//

#ifndef POBI_SHOWTIMEREPOSITORY_H
#define POBI_SHOWTIMEREPOSITORY_H
#include "Showtime.h"

typedef boost::local_time::local_date_time LTime;

typedef boost::local_time::time_zone_ptr TZone;

class ShowtimeRepository
{
private:
	std::vector<showtimePtr> elements;
public:
	bool create(const showtimePtr &element);
	bool remove(const showtimePtr &element);
	void clear();
	showtimePtr find(const std::string &id);
	showtimePtr findWithMovie(const moviePtr &movie, const LTime &time);
	showtimePtr findWithMovie(const std::string &movieTitle, const LTime &time);
	showtimePtr getElement(int i);
	std::string getInfo();
	int getSize();
	void update();
	int getActualId();
};


#endif //POBI_SHOWTIMEREPOSITORY_H
