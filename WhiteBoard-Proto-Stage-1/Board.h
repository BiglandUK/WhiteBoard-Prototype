#pragma once
#include "SFML/Graphics.hpp"
// A Board is a collection of objects.
class Board {
private:
	unsigned int mWidth, mHeight;
	sf::Color mBackgroundColour;
	float mFriction;

public:
	Board(unsigned int width = 1280, unsigned int height = 720);

	void Render(sf::RenderWindow& window);
};