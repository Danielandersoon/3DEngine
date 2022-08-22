#pragma once
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Component.h"

class CollisionBox : 
	public Component
{
public:
	// Box collider constructor
	CollisionBox(float width, float height, sf::Vector3i positionOfParent, sf::Vector3i positionToParent);

	// Circle collider constructor
	CollisionBox(float radius, sf::Vector3f positionToParent);

	void CheckCollisions();

	bool topCollision, bottomCollision, leftCollision, rightCollision;
};

