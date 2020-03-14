#pragma once
#include "SFML/Graphics.hpp"
#include "Textbox.h"

enum class Property{NullProperty = 0, Position, Move, Bounce, Motor};

// Base class for all object properties
class ObjectProperty {
public:
	ObjectProperty(const Property& type, bool canRemove = false, bool canDisable = false);

	Property GetType();

private:
	Property mPropertyType;
	bool mCanRemove;
	bool mCanDisable;
};


//ObjectPosition - stores an objects position and origin (it's primary point, used for rotation, etc.)
// This is needed for an object to be displayed, and to be grabbed by the mouse.
class ObjectPosition: public ObjectProperty {
public:
	ObjectPosition(float x = 0, float y = 0);

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& position);
	sf::Vector2f GetPosition() const;

	void SetOrigin(const sf::Vector2f& origin);
	sf::Vector2f GetOrigin()const;

	bool OnClick(const sf::Vector2f& mousePos); // returns true if grabbed by mouse
	void OnRelease();
	bool IsGrabbed() const;


	void Update(float time, const sf::Vector2f& mousePos);

private:
	sf::Vector2f mPosition;
	sf::Vector2f mOrigin;
	bool mGrabbed;
	sf::Vector2f mPreviousMousePosition;


	bool IsInside(const sf::Vector2f& mousePos);
};


// ObjectMovement - allows an object to move, autonomously or via the mouse.
class ObjectMovement : public ObjectProperty {
public:
	ObjectMovement();
	~ObjectMovement();

	void SetDirection(const sf::Vector2f& direction);
	const sf::Vector2f& GetDirection() const;
	sf::Vector2f& GetDirection();

	void SetVelocity(const sf::Vector2f& velocity);
	const sf::Vector2f& GetVelocity() const;
	sf::Vector2f& GetVelocity();

	void ReduceSpeed(const float speed);
	void Stop();
	bool IsStopped()const;

	void OnRelease();

	void Update(float time, const sf::Vector2f& mousePos);
	void Render(sf::RenderWindow& window);

	bool DoesBounce() const;
	void SetBounce(bool bounce);

	void CollideLR(); // Collision on left or right
	void CollideTB(); // Collision on top or bottom

private:
	sf::Vector2f mDirection; // the direction the object is facing/heading - used as initial direction when the object moves from rest.
	sf::Vector2f mVelocity;
	float mMaxVelocityMagnitude;
	bool mGrabbed, mBounce;

	Textbox txtBox;
};
