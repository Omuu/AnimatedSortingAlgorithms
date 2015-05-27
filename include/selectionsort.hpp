#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP

#include <vector>

namespace sf{
	class RenderWindow;
}

namespace Sort
{
	class Handle;

	void selectionSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle);

	void selectionSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle);
}

#endif