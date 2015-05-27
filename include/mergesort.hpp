#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <vector>

namespace sf {
	class RenderWindow;
}

namespace Sort{

	class Handle;

	void mergeSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Sort::Handle* handle);

	void mergeSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool& interrupt, sf::RenderWindow& target, Sort::Handle* handle);

	void merge(std::vector<float>::iterator &first, std::vector<float>::iterator &middle, std::vector<float>::iterator &last, bool& interrupt, sf::RenderWindow& target, Sort::Handle* handle);

}

#endif