#pragma once
#include "Animator.h"
#include "CollisionBox.h"
#include "Text.h"

class GameObject
{
public:
	sf::Vector3i position;
	sf::FloatRect scale;
	float rotationX;
};

