//
// Created by Bartek on 10.01.2020.
//

#include "AvaliableException.h"
AvaliableException::AvaliableException(const std::string &str)
	: std::logic_error(str)
{

}
