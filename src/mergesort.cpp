#include "mergesort.hpp"

#include <SFML\Graphics.hpp>

#include "Handle.hpp"


void Sort::mergeSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Sort::Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	mergeSort(heightsVec.begin(), heightsVec.end(), interrupt, target, handle);
	(*handle)(interrupt);
	handle->flourish(1.5, interrupt);
}

void Sort::mergeSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool& interrupt, sf::RenderWindow& target, Sort::Handle* handle)
{
	if ((last - first > 1) && (!interrupt))
	{
		std::vector<float>::iterator middle = first + (last - first) / 2;
		mergeSort(first, middle, interrupt, target, handle);
		mergeSort(middle, last, interrupt, target, handle);

		merge(first, middle, last, interrupt, target, handle);
	}
}

void Sort::merge(std::vector<float>::iterator &first, std::vector<float>::iterator &middle, std::vector<float>::iterator &last, bool& interrupt, sf::RenderWindow& target, Sort::Handle* handle)
{
	sf::Time delay = sf::milliseconds(2);
	sf::Clock clock;

	auto sz = std::distance(first, last);

	std::vector<float> sortedHeights(sz, 0.0f);

	std::vector<float>::iterator it1 = first;
	std::vector<float>::iterator it2 = middle;

	int index = 0;

	if (!interrupt)
	{
		while ((it1 < middle) && (it2 < last))
		{
			handle->makeBarActive(it1);
			handle->makeBarActive(it2);

			(*handle)(interrupt);

			while (clock.getElapsedTime() < delay){}
			clock.restart();

			handle->makeBarInactive(it1);
			handle->makeBarInactive(it2);

			*it1 < *it2 ?
				(sortedHeights[index++] = *(it1++)) :
				(sortedHeights[index++] = *(it2++));
		}

		while (it1 < middle)
		{
			sortedHeights[index++] = *(it1++);
		}
		while (it2 < last)
		{
			sortedHeights[index++] = *(it2++);
		}

		for (size_t i = 0; i < sortedHeights.size(); ++i)
		{
			*(first + i) = sortedHeights[i];

		}
	}

}