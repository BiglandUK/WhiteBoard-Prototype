#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Textbox.h"

using Objects = std::vector<std::shared_ptr<Object>>;

class SysMovement {
public:
	SysMovement(Objects& objects);

	void Update(float time, const sf::Vector2f& mousePos);
	void OnClick(const sf::Vector2f& mousePos);
	void OnRelease();

	void Render(sf::RenderWindow& window);

	// Calculates an "exponential moving average" to smooth out the mouse velocity.
	// Input delta time and the current velocity (based purely on delta movement and delta time from this and previous frame).
	// Uses previous velocity 
	// Taken from https://mortoray.com/2015/04/08/measuring-finger-mouse-velocity-at-release-time/
	// 
	sf::Vector2f ExpMovingAverageVelocity(double time, sf::Vector2f& currentVelocity);

private:
	Objects& mRefObjects;
	sf::Vector2f mPreviousMousePosition;
	sf::Vector2f mMouseEMAVelocity;
	float mFriction;

	Textbox txtBox;

	void RestrictBoardBoundaries(sf::Vector2f& pos);

};