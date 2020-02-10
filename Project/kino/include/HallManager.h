//
// Created by student on 30.12.2019.
//

#ifndef POBI_HALLMANAGER_H
#define POBI_HALLMANAGER_H
#include "HallRepository.h"
#include "MovieRepository.h"

class HallManager
{
private:
	HallRepository halls;
public:
	virtual ~HallManager();
	HallManager();
	bool createHall(const std::string &id, const std::string &name, int rows, int seatsInRow, bool available3d);
	bool createHall(hallPtr);
	bool removeHall(std::string id);
	bool removeHall(hallPtr);
	bool addMovieToHall(std::string id, const moviePtr &movie);
	std::string getHallsInfo();
	std::string getMoviesInHallInfo(std::string hallId);
	const std::vector<hallPtr> &getElements() const;
	int countHall();
	hallPtr operator()(std::string id);
};


#endif //POBI_HALLMANAGER_H
