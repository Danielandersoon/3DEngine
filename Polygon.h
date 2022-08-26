#pragma once
#include <CMath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Eng {

	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int thickness, sf::Color colour,
		sf::RenderWindow* app_ptr)
	{
		sf::ConvexShape triangle;
		triangle.setPointCount(3);

		triangle.setPoint(0, sf::Vector2f(x1, y1));
		triangle.setPoint(1, sf::Vector2f(x2, y2));
		triangle.setPoint(2, sf::Vector2f(x3, y3));

		app_ptr->draw(triangle);
	}
}
