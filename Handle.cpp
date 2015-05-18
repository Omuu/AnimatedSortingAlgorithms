//#include <SFML\sfml.h>
#include <SFML\Graphics.hpp>

#include <vector>
#include <string>
#include <cmath>

#include "Handle.hpp"
#include "Bar.hpp"

#include "quicksort.hpp"
#include "mergesort.hpp"
#include "bubblesort.hpp"
#include "insertionsort.hpp"
#include "selectionsort.hpp"
#include "heapsort.hpp"

#include "randomtoolkit.hpp"

using Sort::Handle;
using Sort::Bar;

Handle::Handle(sf::RenderWindow& window, std::vector<Bar>* bars, std::vector<float>* heightsVec, bool& close) :
	m_window(window),
	m_barVec(bars),
	m_heightsVec(heightsVec),
	m_busy(false),
	m_interrupt(false),
	m_close(close),
	m_numOfBars(bars->size()),
	m_currAlgo(AlgoName::QUICKSORT),
	m_windowHeight(window.getSize().y),
	m_windowWidth(window.getSize().x)
{
	m_maxBarHeight = bars->back().getHeight();
}

void Handle::operator()()
{
	(*this)(m_interrupt);
}

void Handle::operator()(bool & interrupt)
{
	if (m_close)
	{
		m_window.close();
		return;
	}
	// check all the window's events that were triggered since the last iteration of the loop
	static sf::Event event;
	while (m_window.pollEvent(event))
	{
		// check the type of the event...
		switch (event.type)
		{
			// window closed
			case sf::Event::Closed:
				m_window.close();
				break;

				// key pressed
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						interrupt = true;
						m_close = true;
						m_window.close();
						break;

					case sf::Keyboard::Space:
						interrupt = (interrupt ? false : true);
						break;

					/*case sf::Keyboard::F:
						flourish(sf::Color::Blue, 1.5, interrupt);
						break;*/

					case sf::Keyboard::R:
						if (!m_busy) {
							m_busy = true;
							shuffleHeights(*m_heightsVec);
							m_busy = false;
						}
						break;

					case sf::Keyboard::Up:
						if (!m_busy) {
							m_busy = true;
							changeNumOfBars(10);
							m_busy = false;
						}
						break;

					case sf::Keyboard::Down:
						if (!m_busy) {
							m_busy = true;
							changeNumOfBars(-10);
							m_busy = false;
						}
						break;

					case sf::Keyboard::S:
						if (!m_busy) {
							m_busy = true;
							switch (m_currAlgo)
							{
								case AlgoName::QUICKSORT:
									quickSort(*m_heightsVec, interrupt, m_window, this);
									if (interrupt)
										interrupt = false;
									break;

								case AlgoName::MERGESORT:
									mergeSort(*m_heightsVec, interrupt, m_window, this);
									if (interrupt)
										interrupt = false;
									break;

								case AlgoName::BUBBLESORT:
									bubbleSort(*m_heightsVec, interrupt, m_window, this);
									if (interrupt)
										interrupt = false;
									break;

								case AlgoName::INSERTIONSORT:
									insertionSort(*m_heightsVec, interrupt, m_window, this);
									if (interrupt)
										interrupt = false;
									break;

								case AlgoName::SELECTIONSORT:
									selectionSort(*m_heightsVec, interrupt, m_window, this);
									if (interrupt)
										interrupt = false;
									break;

								case AlgoName::HEAPSORT:
									heapSort(*m_heightsVec, interrupt, m_window, this);
									if (interrupt)
										interrupt = false;
									break;
							}
							m_busy = false;
						}
						break;

					case sf::Keyboard::Num1:
						m_currAlgo = AlgoName::QUICKSORT;
						colorAlgoText(AlgoName::QUICKSORT);
						break;

					case sf::Keyboard::Num2:
						m_currAlgo = AlgoName::MERGESORT;
						colorAlgoText(AlgoName::MERGESORT);
						break;

					case sf::Keyboard::Num3:
						m_currAlgo = AlgoName::BUBBLESORT;
						colorAlgoText(AlgoName::BUBBLESORT);
						break;

					case sf::Keyboard::Num4:
						m_currAlgo = AlgoName::INSERTIONSORT;
						colorAlgoText(AlgoName::INSERTIONSORT);
						break;

					case sf::Keyboard::Num5:
						m_currAlgo = AlgoName::SELECTIONSORT;
						colorAlgoText(AlgoName::SELECTIONSORT);
						break;

					case sf::Keyboard::Num6:
						m_currAlgo = AlgoName::HEAPSORT;
						colorAlgoText(AlgoName::HEAPSORT);
						break;
				}
				break;

				// don't process other types of events
			default:
				break;
		}
	}

	// clear the window with black color
	m_window.clear(sf::Color::Black);

	syncHeights(*m_barVec, *m_heightsVec);

	// draw everything here...
	for (auto x : *m_barVec) {
		x.moveToBottom(m_windowHeight);
		m_window.draw(x);
	}

	for (const auto & y : m_textMap) {
		m_window.draw(y.second);
	}

	for (const auto & t : m_textVec) {
		m_window.draw(t);
	}

	m_window.draw(m_numOfBarsText);

	// end the current frame
	m_window.display();
}

void Handle::colorBar(const std::vector<float>::iterator &it, sf::Color col)
{
	auto dist = std::distance(m_heightsVec->begin(), it);
	m_barVec->at(dist).setColor(col);
}

void Handle::colorBar(size_t index, sf::Color col)
{
	m_barVec->at(index).setColor(col);
}

void Handle::flourish(sf::Color col, float timeInSeconds, bool& interrupt)
{
	if (interrupt)
	{
		return;
	}

	static sf::Event event;
	sf::Clock clock;

	auto num = m_barVec->size();
	auto delay = sf::seconds(timeInSeconds) / float(num);

	for (size_t i = 0; i < m_barVec->size(); ++i)
	{
		if (interrupt)
			break;

		m_window.clear(sf::Color::Black);
		(*m_barVec)[i].setColor(col);

		while (m_window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
				case sf::Event::Closed:
					m_window.close();
					break;

					// key pressed
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Escape:
							interrupt = true;
							m_close = true;
							m_window.close();
							break;

						case sf::Keyboard::Space:
							interrupt = true;
							break;
					}

					// we don't process other types of events
				default:
					break;
			}
		}

		for (auto y = m_barVec->begin(); y < m_barVec->end(); ++y)
			m_window.draw(*y);
			

		for (const auto & y : m_textMap) {
			m_window.draw(y.second);
		}

		for (const auto & y : m_textMap) {
			m_window.draw(y.second);
		}

		for (const auto & t : m_textVec) {
			m_window.draw(t);
		}

		m_window.draw(m_numOfBarsText);

		while (clock.getElapsedTime() < delay){}
		clock.restart();

		m_window.display();
	}

	for (auto z = m_barVec->begin(); z < m_barVec->end(); ++z)
		z->setColor(sf::Color::Green);

	interrupt = false;
}

void Sort::shuffleHeights(std::vector<float> & heightVec)
{
	rnd::randomize();
	std::shuffle(heightVec.begin(), heightVec.end(), rnd::engine());

}

void Sort::syncHeights(std::vector<Bar> &barVec, std::vector<float> &heightsVec)
{
	if (barVec.size() != heightsVec.size())
	{
		return;
	}
	auto itBegin = barVec.begin();
	auto itEnd = barVec.end();
	for (size_t i = 0; itBegin + i < itEnd; ++i)
	{
		(itBegin + i)->setHeight(heightsVec[i]);
	}
}

void Handle::addAlgoText(AlgoName name, sf::Text text)
{
	m_textMap[name] = text;
}

void Handle::colorAlgoText(AlgoName algo)
{
	for (auto & x : m_textMap)
	{
		x.second.setColor(sf::Color::White);
	}
	m_textMap[algo].setColor(sf::Color::Red);
}

void Handle::addText(sf::Text text)
{
	m_textVec.push_back(text);
}

void Handle::setFont(sf::Font* font) {
	m_font = font;
	m_numOfBarsText.setFont(*m_font);
	m_numOfBarsText.setString(sf::String("Number of bars: ") + std::to_string(m_numOfBars));
	m_numOfBarsText.setCharacterSize(15);
	m_numOfBarsText.setPosition(5, 45);
}

void Handle::changeNumOfBars(int amount)
{
	if ((amount > 0) && (m_numOfBars + amount <= 1500))
		m_numOfBars += amount;

	else if ((amount < 0) && (m_numOfBars - std::abs(amount) > 0))
	{
		m_numOfBars -= std::abs(amount);
	}

	else
		return;

	m_numOfBarsText.setString(sf::String("Number of bars: ") + std::to_string(m_numOfBars));

	// the distance between each bar
	float separation = 0.0f;

	float barWidth = (m_windowWidth - m_numOfBars * separation) / float(m_numOfBars);

	*m_barVec = std::vector < Sort::Bar > {};
	*m_heightsVec = std::vector < float > {};

	for (size_t i = 0; i < m_numOfBars; ++i)
	{
		float barHeight = float(m_maxBarHeight) * (i + 1) / m_numOfBars;
		m_heightsVec->push_back(barHeight);
		m_barVec->push_back(Sort::Bar{ barWidth, barHeight, (barWidth + separation)*i, float(m_windowHeight) - barHeight, sf::Color::Green });
	}

	shuffleHeights(*m_heightsVec);

	// clear the window with black color
	m_window.clear(sf::Color::Black);

	syncHeights(*m_barVec, *m_heightsVec);

	// draw everything here...
	for (auto x : *m_barVec) {
		x.moveToBottom(m_windowHeight);
		m_window.draw(x);
		//x.drawBar(m_window);
	}

	for (const auto & y : m_textMap) {
		m_window.draw(y.second);
	}

	for (const auto & t : m_textVec) {
		m_window.draw(t);
	}

	m_window.draw(m_numOfBarsText);

	// end the current frame
	m_window.display();
}