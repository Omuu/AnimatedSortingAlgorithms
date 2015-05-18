#include "bubblesort.hpp"
#include "Handle.hpp"

#include <SFML\Graphics.hpp>

void Sort::bubbleSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Sort::Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	bubbleSort(heightsVec.begin(), heightsVec.end(), interrupt, target, handle);
	(*handle)(interrupt);
	handle->flourish(sf::Color::Blue, 1.5, interrupt);
}

void Sort::bubbleSort(std::vector<float>::iterator &first, std::vector<float>::iterator &last, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	bool done = false;
	auto to = last;

	int count = 0;

	while ((!done) && (!interrupt))
	{
		done = true;
		for (auto it = first; it < (to - 1); ++it)
		{
			if (interrupt)
				break;

			if (*it > *(it + 1))
			{
				done = false;
				std::iter_swap(it, it + 1);

				if (count == 3) {
					handle->colorBar(it, sf::Color::Red);
					handle->colorBar(it + 1, sf::Color::Red);

					(*handle)(interrupt);

					handle->colorBar(it, sf::Color::Green);
					handle->colorBar(it + 1, sf::Color::Green);

					count = 0;
				}
				++count;
			}

		}
		--to;
	}
}