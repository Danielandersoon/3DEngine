#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(float coliderWidth, float coliderHeight, sf::Vector2i positionOfParent, sf::Vector2i coliderPositionToParent,
	double in_mass, double terminalVel)
{
	collider = new CollisionBox(coliderWidth, coliderHeight, positionOfParent, coliderPositionToParent);
	
	mass = mass;
	terminalVelocity = terminalVel;
}

void PhysicsBody::update(float dt)
{

	// Falling 
	if (Velocity.y < terminalVelocity)
		applyGravity(dt);
}

void PhysicsBody::applyGravity(float dt)
{
	Velocity.y = Velocity.y + g * dt;
}
