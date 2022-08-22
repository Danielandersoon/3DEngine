#pragma once
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct Animation
{
	Animation(std::string name, int noSprites);

	void nextFrame();
	void previousFrame();
	void gotoFrame(int targetFrame);

	int m_noSprites;
	int currentSprite;

	sf::Sprite* spriteArray;
	sf::Texture sheet;
};

