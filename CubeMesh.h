#pragma once

#include <SFML/Graphics.hpp>



namespace engine
{
	template <typename T>
	class CubeMesh
		: public sf::Drawable
	{
		public:
		// Default constructor creates a cube of size 0,0,0 at co-ordinate 0,0,0
			CubeMesh();
			CubeMesh(T inxPos, T inyPos, T inzPos, T inxSize, T inySize, T inzSize);
			CubeMesh(const sf::Vector3<T> position, const sf::Vector3<T> size);

			draw(sf::Vector3f cameraPosition, sf::Vector2f cameraRotation);

	public:
		T xPos;
		T yPos;
		T zPos;
		T xSize;
		T ySize;
		T zSize;

	};



}