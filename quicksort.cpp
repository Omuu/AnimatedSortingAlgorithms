#include "quicksort.hpp"
#include "Handle.hpp"

#include <vector>

//#include <SFML/sfml.h>
#include <SFML/Graphics.hpp>


void Sort::quickSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	Sort::quickSort(heightsVec.begin(), heightsVec.end(), interrupt, target, handle);
	handle->flourish(sf::Color::Blue, 1.5, interrupt);
}

void Sort::quickSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	sf::Int32 delay = 5;
	sf::Clock clock;

	//(*handle)(interrupt);

	if ((last - first > 1) && (!interrupt))
	{
		const float b = *first;
		std::vector<float>::iterator split = std::partition(first + 1, last, [&](const float & a){ return a < b; });

		handle->colorBar(first, sf::Color::Red);
		handle->colorBar(split - 1, sf::Color::Red);

		std::iter_swap(first, split - 1);

		(*handle)(interrupt);
		// wait a moment
		while (clock.getElapsedTime() < sf::milliseconds(delay)){}
		clock.restart();

		handle->colorBar(first, sf::Color::Green);
		handle->colorBar(split - 1, sf::Color::Green);

		quickSort(first, split - 1, interrupt, target, handle);
		quickSort(split, last, interrupt, target, handle);
	}
}