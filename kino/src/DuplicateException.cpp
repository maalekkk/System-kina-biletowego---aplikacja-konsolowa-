//
// Created by Bartek on 10.01.2020.
//

#include "DuplicateException.h"
DuplicateException::DuplicateException(const std::string &str)
	: std::logic_error(str)
{

}