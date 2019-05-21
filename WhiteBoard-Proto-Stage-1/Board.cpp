#include "Board.h"

Board::Board(unsigned int width, unsigned int height)
	: mWidth(width), mHeight(height),
	mBackgroundColour(sf::Color(0, 255, 200, 0)),
	mFriction(0.5f)
{}

void Board::Render(sf::RenderWindow& window) {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(mWidth, mHeight));
	rectangle.setFillColor(sf::Color(200,200,200,255));
	rectangle.setPosition(0, 0);
		window.draw(rectangle);

}