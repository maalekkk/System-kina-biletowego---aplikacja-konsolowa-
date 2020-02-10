//
// Created by Bartek on 10.01.2020.
//

#ifndef PARAMETEREXCEPTION_H
#define PARAMETEREXCEPTION_H
#include <stdexcept>

class ParameterException: public std::logic_error
{
public:
	ParameterException(const std::string &str);
};


#endif //PARAMETEREXCEPTION_H
