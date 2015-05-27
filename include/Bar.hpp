#ifndef BAR_HPP
#define BAR_HPP

//#include <SFML/sfml.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class RenderTarget;
	class RenderStates;
}

namespace Sort {

	class Bar : public sf::Drawable
	{
	public:
		Bar(float width, float height, float xpos, float ypos, sf::Color color);

		void setHeight(float height);
		float getHeight() const { return m_height; };

		// because SFML considers the top of the window to be y=0, this will adjust the y-coordinate to move the Bar to the bottom of the window
		void moveToBottom(int windowHeight);

		void setColor(sf::Color col);

	private:
		float m_width;
		float m_height;
		float m_xpos;
		float m_ypos;

		sf::Color m_color;
		sf::RectangleShape m_shape;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}

#endif