#pragma once
#include <CMath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Eng {
	struct Line
	{
		Line(int x1, int x2, int y1, int y2, int thickness, sf::Color colour)
		{
			short lineLength = std::sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
			sf::Vector2f centre = sf::Vector2f(x2 - x1, y1 - y2);
			l.setSize(sf::Vector2f(lineLength, thickness));
		};

		sf::RectangleShape l;
	};

	void DrawLine(int x1, int x2, int y1, int y2, int thickness, sf::Color colour, sf::RenderWindow* app_ptr)
	{
		Line line(x1, x2, y1, y2, thickness, colour);

		app_ptr->draw(line.l);
	}

	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int thickness, sf::Color colour,
		sf::RenderWindow* app_ptr)
	{
		DrawLine(x1, x2, y1, y2, thickness, colour, app_ptr);
		DrawLine(x2, x3, y2, y3, thickness, colour, app_ptr);
		DrawLine(x3, x1, y3, y1, thickness, colour, app_ptr);
	}
}
