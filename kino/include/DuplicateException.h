//
// Created by Bartek on 10.01.2020.
//

#ifndef DUPLICATEEXCEPTION_H
#define DUPLICATEEXCEPTION_H
#include <stdexcept>

class DuplicateException: public std::logic_error
{
public:
	DuplicateException(const std::string &str);
};


#endif //DUPLICATEEXCEPTION_H