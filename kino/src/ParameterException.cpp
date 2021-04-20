//
// Created by Bartek on 10.01.2020.
//

#include "ParameterException.h"
ParameterException::ParameterException(const std::string& str)
	: std::logic_error(str)
{

}
