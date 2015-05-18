#include "insertionsort.hpp"
#include "Handle.hpp"

#include <SFML\Graphics.hpp>

#include <algorithm>

void Sort::insertionSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Sort::Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	insertionSort(heightsVec.begin(), heightsVec.end(), interrupt, target, handle);
	(*handle)(interrupt);
	handle->flourish(sf::Color::Blue, 1.5, interrupt);
}

void Sort::insertionSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	sf::Int32 delay = 10;
	sf::Clock clock;

	for (auto it = first; it != last; ++it)
	{
		if (interrupt)
			break;

		auto n_first = it;
		auto next = n_first;
		auto fs = std::upper_bound(first, it, *it);
		auto ls = it + 1;

		while (fs != next) {

			handle->colorBar(fs, sf::Color::Red);
			handle->colorBar(next, sf::Color::Red);

			std::iter_swap(fs, next);

			(*handle)(interrupt);

			handle->colorBar(fs++, sf::Color::Green);
			handle->colorBar(next++, sf::Color::Green);

			//while (clock.getElapsedTime() < sf::microseconds(delay)){}
			//clock.restart();

			if (next == ls) {
				next = n_first;
			}
			else if (fs == n_first) {
				n_first = next;
			}
		}

		(*handle)(interrupt);
	}
}