#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include <vector>

namespace sf{
	class RenderWindow;
}

namespace Sort
{
	class Handle;
	
	void bubbleSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle);

	void bubbleSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle);
}

#endif