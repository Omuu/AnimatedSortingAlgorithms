#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <vector>

namespace sf {
	class RenderWindow;
}

namespace Sort
{
	class Handle;

	void quickSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle);

	void quickSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle);
}

#endif