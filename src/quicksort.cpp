#include "quicksort.hpp"
#include "Handle.hpp"

#include <vector>

#include <SFML/Graphics.hpp>


void Sort::quickSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	Sort::quickSort(heightsVec.begin(), heightsVec.end(), interrupt, target, handle);
	handle->flourish(1.5, interrupt);
}

void Sort::quickSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	sf::Int32 delay = 5;
	sf::Clock clock;

	if ((last - first > 1) && (!interrupt))
	{
		const float b = *first;
		std::vector<float>::iterator split = std::partition(first + 1, last, [&](const float & a){ return a < b; });

		handle->makeBarActive(first);
		handle->makeBarActive(split - 1);

		std::iter_swap(first, split - 1);

		(*handle)(interrupt);
		// wait a moment
		while (clock.getElapsedTime() < sf::milliseconds(delay)){}
		clock.restart();

		handle->makeBarInactive(first);
		handle->makeBarInactive(split - 1);

		quickSort(first, split - 1, interrupt, target, handle);
		quickSort(split, last, interrupt, target, handle);
	}
}