#pragma once
#include "GameObject.h"
class Tile :
    public GameObject
{
    // Static constructor
    Tile(std::string name, bool solid);

    // Animated constructor
    Tile(std::string name, bool solid, int noSprites);

public:


private:
    sf::Vector2f position;

    Animator animator;

};

