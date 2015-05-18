#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include <vector>

namespace sf{
	class RenderWindow;
}

namespace Sort
{
	class Handle;

	void insertionSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle);

	void insertionSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle);
}

#endif