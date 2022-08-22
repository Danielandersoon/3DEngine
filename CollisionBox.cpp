#include "CollisionBox.h"

CollisionBox::CollisionBox(float width, float height, sf::Vector2i positionOfParent, sf::Vector2i positionToParent)
{
	collider.width = width;
	collider.height = height;
	
	collider.left = positionOfParent.x + positionToParent.x;
	collider.top = positionOfParent.y + positionToParent.y;
}
