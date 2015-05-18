#include "heapsort.hpp"
#include "Handle.hpp"

#include <SFML\Graphics.hpp>

#include <algorithm>

void Sort::heapSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle)
{
	if (heightsVec.size() < 2)
		return;

	makeHeap(heightsVec, interrupt, target, handle);
	auto end = heightsVec.size() - 1;
	while (end > 0)
	{
		if (interrupt)
			break;

		handle->colorBar(end, sf::Color::Red);
		std::swap(heightsVec[0], heightsVec[end]);
		siftDown(heightsVec, 0, end, interrupt, target, handle);
		handle->colorBar(end, sf::Color::Green);
		--end;
	}
	
	(*handle)(interrupt);
	handle->flourish(sf::Color::Blue, 1.5, interrupt);
}

void Sort::siftDown(std::vector<float>& heap, int i, int max, bool & interrupt, sf::RenderWindow& target, Handle* handle) {
	int i_big, c1, c2;

	sf::Int32 delay = 5;
	sf::Clock clock;

	while (i < max) {
		if (interrupt)
			break;

		i_big = i;
		c1 = (2 * i) + 1;
		c2 = c1 + 1;
		if (c1<max && heap[c1]>heap[i_big])
			i_big = c1;
		if (c2<max && heap[c2]>heap[i_big])
			i_big = c2;
		if (i_big == i) return;

		handle->colorBar(i, sf::Color::Red);
		handle->colorBar(i_big, sf::Color::Red);

		std::swap(heap[i], heap[i_big]);

		(*handle)(interrupt);

		handle->colorBar(i, sf::Color::Green);
		handle->colorBar(i_big, sf::Color::Green);

		//while (clock.getElapsedTime() < sf::microseconds(delay)){}
		//clock.restart();

		i = i_big;
	}
}

void Sort::makeHeap(std::vector<float>& arr, bool & interrupt, sf::RenderWindow& target, Handle* handle) {
	int i = (arr.size() / 2) - 1;
	while (i >= 0) {
		if (interrupt)
			break;

		handle->colorBar(i, sf::Color::Blue);

		siftDown(arr, i, arr.size(), interrupt, target, handle);

		handle->colorBar(i, sf::Color::Green);

		--i;
	}
}