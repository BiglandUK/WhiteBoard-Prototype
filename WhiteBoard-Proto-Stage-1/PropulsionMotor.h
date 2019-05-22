#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectProperty.h"
// Propulsion Motor
// a SubProperty for the MovementProperty.

class Textbox;

class PropulsionMotor : public ObjectProperty{
public:
	enum class Type { Constant, TimePulse, MinSpeedPulse };

	PropulsionMotor(Type type = Type::Constant, Textbox* txtBox = 0);

	void Update(float time, sf::Vector2f& velocity, const sf::Vector2f& direction);

	void ChangeType(Type type);
	Type GetType()const;

	void SetUpTextBox(Textbox* txtBox);
	void SetRunningDuration(float duration);
	void SetIdleDuration(float duration);
	void SetMinSpeedTrigger(float speed);
	void SetAcceleration(float acceleration);
	void SetSpeed(float speed);

private:
	bool mRunning; // whether the motor is running or not
	Type mType;

	float mMinSpeedTrigger; // Used by minimum speed
	float mRunningDuration, mIdleDuration, mCounter; // Used by timer

	float mAcceleration; // whether magnitude is an acceleration or a set speed.
	float mSetSpeed; // functions as either acceleration or set speed.

	Textbox* pTxtBox;


	void TimedMotor(float time, sf::Vector2f& velocity);
	void ToggleMotor();
	void SwitchToRunning();
	void SwitchToIdle();
};