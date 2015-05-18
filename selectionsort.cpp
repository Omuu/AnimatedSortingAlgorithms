#include "selectionsort.hpp"
#include "Handle.hpp"

#include <SFML\Graphics.hpp>

#include <algorithm>

void Sort::selectionSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	selectionSort(heightsVec.begin(), heightsVec.end(), interrupt, target, handle);
	(*handle)(interrupt);
	handle->flourish(sf::Color::Blue, 1.5, interrupt);
}

void Sort::selectionSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	//sf::Int32 delay = 5;
	//sf::Clock clock;

	for (auto it = first; it != last; ++it)
	{
		if (interrupt)
			break;

		auto smallest = it;
		auto current = it;
		while (current != last)
		{
			if (*current < *smallest)
				smallest = current;
			++current;
		}

		handle->colorBar(it, sf::Color::Red);
		handle->colorBar(smallest, sf::Color::Red);

		std::iter_swap(it, smallest);

		(*handle)(interrupt);

		/*while (clock.getElapsedTime() < sf::milliseconds(delay)){}
		clock.restart();*/

		handle->colorBar(it, sf::Color::Green);
		handle->colorBar(smallest, sf::Color::Green);
	}
}