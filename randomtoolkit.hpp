/*

A small toolkit to cope with the random number facilities of C++11.

*/

#ifndef RANDOMTOOLKIT_HPP
#define RANDOMTOOLKIT_HPP

#include <random>

namespace rnd {

	std::mt19937 & engine();

	void randomize();

	int getNumber(int from, int to);

	double getNumber(double from, double to);

}

#endif