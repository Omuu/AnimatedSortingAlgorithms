#include "bubblesort.hpp"
#include "Handle.hpp"

#include <SFML\Graphics.hpp>

void Sort::bubbleSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Sort::Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	bubbleSort(heightsVec.begin(), heightsVec.end(), interrupt, target, handle);
	(*handle)(interrupt);
	handle->flourish(1.5, interrupt);
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
					handle->makeBarActive(it);
					handle->makeBarActive(it + 1);

					(*handle)(interrupt);

					handle->makeBarInactive(it);
					handle->makeBarInactive(it + 1);

					count = 0;
				}
				++count;
			}

		}
		--to;
	}
}