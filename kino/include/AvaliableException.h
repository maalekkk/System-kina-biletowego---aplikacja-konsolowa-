//
// Created by Bartek on 10.01.2020.
//

#ifndef AVALIABLEEXCEPTION_H
#define AVALIABLEEXCEPTION_H
#include <stdexcept>

class AvaliableException: public std::logic_error
{
public:
	AvaliableException(const std::string &str);
};


#endif //AVALIABLEEXCEPTION_H
