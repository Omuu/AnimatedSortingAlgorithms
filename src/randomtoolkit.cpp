#include "randomtoolkit.hpp"

#include <random>

std::mt19937 & rnd::engine()
{
	static std::mt19937 eng{};
	return eng;
}

void rnd::randomize()
{
	static std::random_device rd{};
	engine().seed(rd());
}

int rnd::getNumber(int from, int to)
{
	static std::uniform_int_distribution<> dist{};
	return dist(engine(), std::uniform_int_distribution<>::param_type{ from, to });
}

double rnd::getNumber(double from, double to)
{
	static std::uniform_real_distribution<> dist{};
	return dist(engine(), std::uniform_real_distribution<>::param_type{ from, to });
}