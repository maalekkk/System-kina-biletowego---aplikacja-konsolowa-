//
// Created by student on 30.12.2019.
//
#include "ClientType.h"

ClientType::ClientType(int movieCount)
	: movieCount(movieCount)
{}

ClientType::~ClientType()
{}

int ClientType::getMovieCount()
{
	return this->movieCount;
}