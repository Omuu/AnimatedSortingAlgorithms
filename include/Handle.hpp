#ifndef HANDLE_HPP
#define HANDLE_HPP

#include <vector>
#include <map>
#include <SFML\Graphics\Text.hpp>

namespace sf {
	class RenderWindow;
	class Color;
	class Font;
}

namespace Sort {

	class Bar;

	class Handle
	{
	public:
		Handle(sf::RenderWindow & window, std::vector<Bar>* bars, std::vector<float>* heightsVec, bool& close);

		void operator()();
		void operator()(bool& interrupt);

		// given an iterator to a value in heightsVec, this will change the corresponding Bar to the color col
		void colorBar(const std::vector<float>::iterator &it, sf::Color col);

		// given the index of a bar, this will change its color to col
		void colorBar(size_t index, sf::Color col);

		// changes the colour of the given bar to m_activeCol
		void makeBarActive(const std::vector<float>::iterator &it);
		void makeBarActive(size_t index);

		// changes the colour of the given bar to m_inactiveCol
		void makeBarInactive(const std::vector<float>::iterator &it);
		void makeBarInactive(size_t index);

		// sweeps the bars with the colour col - intended to finish off a sort
		void flourish(sf::Color col, float timeInSeconds, bool& interrupt);

		// sweeps the bars with the colour m_flourishCol
		void flourish(float timeInSeconds, bool& interrupt);

		enum class AlgoName { QUICKSORT, MERGESORT, BUBBLESORT, INSERTIONSORT, SELECTIONSORT, HEAPSORT };

		void addAlgoText(AlgoName name, sf::Text text);

		void addText(sf::Text text);

		void setFont(sf::Font* font);

		// setters and getters for the colours of the bars when active, when inactive, and for the flourish
		void setActiveCol(sf::Color col);
		sf::Color getActiveCol();
		void setInactiveCol(sf::Color col);
		sf::Color getInactiveCol();
		void setFlourishCol(sf::Color col);
		sf::Color getFlourishCol();

	private:
		sf::RenderWindow & m_window;
		std::vector<Sort::Bar>* m_barVec;
		std::vector<float>* m_heightsVec;

		// the colours of the bars when active, when inactive, and for the flourish
		sf::Color m_activeCol;
		sf::Color m_inactiveCol;
		sf::Color m_flourishCol;

		// holds all of the names of the algorithms that will be drawn, indexed by AlgoName
		std::map<AlgoName, sf::Text> m_textMap;

		// holds all of the text (that isn't the name of an algorithm) that will be drawn
		std::vector<sf::Text> m_textVec;

		AlgoName m_currAlgo;

		// this will be true whenever a sort is being undertaken
		// when true, we can exit, but not shuffle or run another sort
		bool m_busy;

		// when true, stop the currently running algorithm but don't close the window
		bool m_interrupt;

		// informs the function 'main' whether or not to close
		bool & m_close;

		int m_windowHeight;
		int m_windowWidth;

		void colorAlgoText(AlgoName algo);

		size_t m_numOfBars;
		sf::Font* m_font;
		sf::Text m_numOfBarsText;

		// this will change the number of bars by 'amount', either increasing if positive or decreasing if negative
		// capped at 1500, must be greater than 0
		void changeNumOfBars(int amount);

		// holds the height of the tallest Bar
		float m_maxBarHeight;
	};

	// given a vector of floats this will randomly change their order
	void shuffleHeights(std::vector<float> & heightsVec);

	void syncHeights(std::vector<Sort::Bar> &barVec, std::vector<float> &heightsVec);

}

#endif