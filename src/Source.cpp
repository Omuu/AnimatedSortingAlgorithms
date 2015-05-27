#include <SFML\Graphics.hpp>

#include <vector>
#include <array>
#include <string>

#include <iostream>
#include <algorithm>

#include "randomtoolkit.hpp"
#include "Bar.hpp"
#include "Handle.hpp"
#include "quicksort.hpp"
#include "mergesort.hpp"


const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

// this is the height of the region in which the Bars are drawn
const int BARS_HEIGHT = 600;

// activeCol is the colour of a bar when it is being compared to another bar
// it is inactiveCol otherwise
const sf::Color INACTIVE_COL = sf::Color::Green;
const sf::Color ACTIVE_COL = sf::Color::Red;
const sf::Color FLOURISH_COL = sf::Color::Blue;

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Algorithms");

	//window.setFramerateLimit(80);

	sf::Font arialFont;

	if (!arialFont.loadFromFile("arial.ttf"))
	{
		std::cout << "Failed to load font.";
	}

	size_t numberOfBars = 1000;

	// the distance between each bar
	float separation = 0.0f;

	float barWidth = (WINDOW_WIDTH - numberOfBars * separation) / float(numberOfBars);

	std::vector<Sort::Bar> bars;

	std::vector<float> heights;

	// the initial arrangement - the bars are sorted by height in ascending order
	for (size_t i = 0; i < numberOfBars; ++i)
	{
		float barHeight = float(BARS_HEIGHT) * (i + 1) / numberOfBars;
		heights.push_back(barHeight);
		bars.push_back(Sort::Bar{ barWidth, barHeight, (barWidth + separation)*i, float(WINDOW_HEIGHT) - barHeight, INACTIVE_COL });
	}

	// exit when true
	bool close = false;

	// 'handle' deals with keyboard input and draws to the window
	// calling handle(true) will abort any currently-running algorithm
	Sort::Handle handle(window, &bars, &heights, close);
	handle.setActiveCol(ACTIVE_COL);
	handle.setInactiveCol(INACTIVE_COL);
	handle.setFlourishCol(FLOURISH_COL);

	// 'handle' holds all of the text to be written to the window
	// it is populated here

	handle.setFont(&arialFont);

	sf::Text algorithmName("1. Quicksort", arialFont);
	algorithmName.setPosition(5, 5);
	algorithmName.setCharacterSize(15);
	algorithmName.setColor(sf::Color::Red);
	handle.addAlgoText(Sort::Handle::AlgoName::QUICKSORT, algorithmName);

	algorithmName.setString("2. Mergesort");
	algorithmName.setPosition(105, 5);
	algorithmName.setColor(sf::Color::White);
	handle.addAlgoText(Sort::Handle::AlgoName::MERGESORT, algorithmName);

	algorithmName.setString("3. Bubble sort");
	algorithmName.setPosition(205, 5);
	algorithmName.setColor(sf::Color::White);
	handle.addAlgoText(Sort::Handle::AlgoName::BUBBLESORT, algorithmName);

	algorithmName.setString("4. Insertion sort");
	algorithmName.setPosition(305, 5);
	algorithmName.setColor(sf::Color::White);
	handle.addAlgoText(Sort::Handle::AlgoName::INSERTIONSORT, algorithmName);

	algorithmName.setString("5. Selection sort");
	algorithmName.setPosition(425, 5);
	algorithmName.setColor(sf::Color::White);
	handle.addAlgoText(Sort::Handle::AlgoName::SELECTIONSORT, algorithmName);

	algorithmName.setString("6. Heap sort");
	algorithmName.setPosition(550, 5);
	algorithmName.setColor(sf::Color::White);
	handle.addAlgoText(Sort::Handle::AlgoName::HEAPSORT, algorithmName);

	sf::Text instructionString("Controls:  (R) to shuffle, (S) to sort, (1-6) to select algorithm, (Space) to interrupt, (Up/Down) to change number of bars, (ESC) to quit", arialFont);
	instructionString.setCharacterSize(15);
	instructionString.setPosition(5, 25);
	handle.addText(instructionString);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		if (close)
			window.close();

		handle();
	}

	return 0;
}