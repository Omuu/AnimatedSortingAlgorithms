#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <vector>

namespace sf{
	class RenderWindow;
}

namespace Sort
{
	class Handle;

	void heapSort(std::vector<float>& heightsVec, bool & interrupt, sf::RenderWindow& target, Handle* handle);

	void siftDown(std::vector<float>& heap, int i, int max, bool & interrupt, sf::RenderWindow& target, Handle* handle);

	void makeHeap(std::vector<float>& arr, bool & interrupt, sf::RenderWindow& target, Handle* handle);

}

#endif