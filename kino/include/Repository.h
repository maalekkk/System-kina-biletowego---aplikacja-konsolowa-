//
// Created by Bartek on 03.01.2020.
//
#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <string>
#include <vector>
#include "boost/lexical_cast.hpp"
#include "DuplicateException.h"
#include "AvaliableException.h"

template<class T>
class Repository
{
private:
	std::vector<T> elements;
public:
	bool create(T element);
	bool remove(T element);
	void clear();
	T find(std::string s);
	T getElement(int i);
	std::string getInfo();
	int getSize();
	const std::vector<T> &getElements() const;

};
template<class T>
bool Repository<T>::create(T element)
{
	for (auto it: elements) {
		if (*it == *element)
			throw DuplicateException("Istnieje juz dany element.");
	}
	elements.push_back(element);
	return true;
}
template<class T>
bool Repository<T>::remove(T element)
{
	for (int i = 0; i < int(elements.size()); i++) {
		if (elements[i] == element) {
			elements.erase(elements.begin() + i);
			return true;
		}
	}
	return false;
}
template<class T>
void Repository<T>::clear()
{
	elements.clear();
}
template<class T>
T Repository<T>::find(std::string s)
{
	for (auto it: elements) {
		if (boost::lexical_cast<std::string>(it->getId()) == s) {
			return it;
		}
	}
	throw AvaliableException("Brak podanego elementu");
}
template<class T>
T Repository<T>::getElement(int i)
{
	if (i <= int(elements.size()))
		return elements[i];
	else
		throw AvaliableException("W naszej bazie nie ma az tyle elementow");
}
template<class T>
std::string Repository<T>::getInfo()
{
	std::stringstream ss;
	ss << "Informacje o repozytorium: \n";
	for (auto it: elements) {
		ss << it->getInfo() << "\n\n";
	}
	return ss.str();
}
template<class T>
int Repository<T>::getSize()
{
	return elements.size();
}
template<class T>
const std::vector<T> &Repository<T>::getElements() const
{
	return elements;
}

#endif //REPOSITORY_H
