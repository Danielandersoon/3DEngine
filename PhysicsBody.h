#pragma once
#include "GameObject.h"
class PhysicsBody :
    public GameObject
{
public:
    PhysicsBody(float coliderWidth, float coliderHeight, sf::Vector2i positionOfParent, sf::Vector2i coliderPositionToParent,
        double in_mass, double terminalVel);

    void update(float dt);

    void applyGravity(float dt);

    double mass;
    double terminalVelocity;

    CollisionBox* collider;

    sf::Vector2f Position;
    sf::Vector2f Velocity;
};

