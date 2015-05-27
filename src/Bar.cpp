#include "Bar.hpp"

#include <SFML/Graphics.hpp>

using Sort::Bar;

Bar::Bar(float width, float height, float xpos, float ypos, sf::Color color) :
m_width(width),
m_height(height),
m_xpos(xpos),
m_ypos(ypos),
m_color(color)
{
	m_shape.setSize(sf::Vector2f(m_width, m_height));
	m_shape.setFillColor(m_color);
	m_shape.setPosition(sf::Vector2f(m_xpos, m_ypos));
};

void Bar::setHeight(float height) {
	m_height = height;
	m_shape.setSize(sf::Vector2f(m_width, m_height));
}

void Bar::setColor(sf::Color col) {
	m_color = col;
	m_shape.setFillColor(m_color);
};

void Bar::moveToBottom(int windowHeight)
{
	m_ypos = float(windowHeight) - m_height;
	m_shape.setPosition(sf::Vector2f(m_xpos, m_ypos));
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}