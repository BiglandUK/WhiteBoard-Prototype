#include "PropulsionMotor.h"
#include "Textbox.h"
PropulsionMotor::PropulsionMotor(Type type, Textbox* txtBox)
	: ObjectProperty(Property::Motor), mType(type), mSetSpeed(0.f), mAcceleration(0.f), mMinSpeedTrigger(0.f), mCounter(0.f), pTxtBox(new Textbox),
	mIdleDuration(0.f), mRunningDuration(0.f), mRunning(false)
{
	SwitchToRunning();
}

void PropulsionMotor::SetUpTextBox(Textbox* txtBox) {
	pTxtBox = txtBox;
}

void PropulsionMotor::Update(float time, sf::Vector2f& velocity, const sf::Vector2f& direction) {
	if (mType == Type::TimePulse) {
		TimedMotor(time, velocity);
	}

	if (mType == Type::MinSpeedPulse) {
		if (std::hypotf(velocity.x, velocity.y) > mMinSpeedTrigger) {
			SwitchToIdle(); // object is going fast enough
			pTxtBox->Add("Motor switched OFF");
			pTxtBox->Add(std::to_string(velocity.x) + " , " + std::to_string(velocity.y));
		}
		else {
			SwitchToRunning(); //object needs to go faster
			pTxtBox->Add("Motor switched on.");
			pTxtBox->Add(std::to_string(velocity.x) + " , " + std::to_string(velocity.y));
		}
	}

	if (!mRunning) {
		pTxtBox->Add("Motor not running.");
		pTxtBox->Add(std::to_string(velocity.x) + " , " + std::to_string(velocity.y));
		return;
	}

	const float currentSpeed = std::hypotf(velocity.x, velocity.y);
	// If the motor will not exceed the current speed, don't do anything.
	// (If the object has been "flicked" by the mouse or a launcher, for example.
	if (mSetSpeed != 0.f && mSetSpeed < currentSpeed) {
		pTxtBox->Add(std::to_string(velocity.x) + " , " + std::to_string(velocity.y));
		return;
	}

	// If forcing to a particular velocity...
	if (mAcceleration == 0.f && mSetSpeed != 0.f) {
		velocity.x = direction.x * mSetSpeed;
		velocity.y = direction.y * mSetSpeed;
		pTxtBox->Add(std::to_string(velocity.x) + " , " + std::to_string(velocity.y));
		return;
	}

	// Acceleration only beyond here.
	if (mAcceleration != 0.f) {
		float newSpeed = currentSpeed + (mAcceleration * time);
		if (mSetSpeed != 0.f && newSpeed > mSetSpeed) {
			newSpeed = mSetSpeed;
		}
		velocity.x = direction.x * newSpeed;
		velocity.y = direction.y * newSpeed;
	}

	// If mAcceleration AND mSetSpeed both equal zero, then nothing will happen.
	// Could even check that at the start, and turn the motor to idle.
	pTxtBox->Add(std::to_string(velocity.x) + " , " + std::to_string(velocity.y));

}

void PropulsionMotor::TimedMotor(float time, sf::Vector2f & velocity) {
	mCounter += time;
	if (mRunning && mRunningDuration > 0.f) {
		if (mCounter > mRunningDuration) {
			mCounter -= mRunningDuration;
			SwitchToIdle();
		}
	}
	else if (!mRunning && mIdleDuration > 0.f) {
		if (mCounter > mIdleDuration) {
			mCounter -= mIdleDuration;
			SwitchToRunning();
		}
	}
}

void PropulsionMotor::ChangeType(Type type) {
	mType = type;
	mCounter = 0.f;
	mMinSpeedTrigger = 0.f;
}

PropulsionMotor::Type PropulsionMotor::GetType()const {
	return mType;
}


void PropulsionMotor::ToggleMotor() {
	mRunning = !mRunning;
}
void PropulsionMotor::SwitchToRunning() {
	mRunning = true;
}
void PropulsionMotor::SwitchToIdle() {
	mRunning = false;
}

void PropulsionMotor::SetAcceleration(float acceleration) {
	mAcceleration = acceleration;
}

void PropulsionMotor::SetSpeed(float speed) {
	mSetSpeed = speed;
}

void PropulsionMotor::SetMinSpeedTrigger(float speed) {
	mMinSpeedTrigger = speed;
}

void PropulsionMotor::SetRunningDuration(float duration) {
	mRunningDuration = duration;
}
void PropulsionMotor::SetIdleDuration(float duration) {
	mIdleDuration = duration;
}