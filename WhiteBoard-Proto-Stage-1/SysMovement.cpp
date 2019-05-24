#include "SysMovement.h"
#include "PropulsionMotor.h"

SysMovement::SysMovement(Objects& objects)
	: mRefObjects(objects), mFriction(40.f)
{
}

// The update moves each object based on whether its held by the mouse and whether
// it has something giving it velocity.
void SysMovement::Update(float time, const sf::Vector2f& mousePos) {
	// calculate how far mouse has moved since last timeframe
	sf::Vector2f difference = static_cast<sf::Vector2f>(mousePos) - mPreviousMousePosition;

	sf::Vector2f velocity;
	// As long as time has passed, use the difference vector to calculate a speed vector for the movement.
	if (time > 0.f) { velocity = sf::Vector2f(difference.x / time, difference.y / time); }
	// (if time is zero, the velocity will also be zero)
	// Calculate the "Exponential Moving Average Velocity of the mouse".
	mMouseEMAVelocity = ExpMovingAverageVelocity(time, velocity);
	for (auto o : mRefObjects) { // for each object
		if (!(o->IsVisible())) { continue; } // ignore invisible objects - should really be "disabled", as invisible can still have an effect.
		
		// Get this object's Position Property - it should have one, as it's mandatory
		auto positionProp = o->GetProperty<ObjectPosition>(Property::Position);
		if (positionProp == nullptr) continue; // skip if there isn't one
				
		// Get this object's Movement Property (it's needed for the Motor Property.
		auto movementProp = o->GetProperty<ObjectMovement>(Property::Move);
		if (movementProp){ // skip if there isn't one
			// Get this object's Propulsion Motor Property
			auto motorProp = o->GetProperty<PropulsionMotor>(Property::Motor);
			if (motorProp) { // If there is one...
				//...get references to the Movement Property's velocity and direction vector...
				sf::Vector2f& vel = movementProp->GetVelocity();
				sf::Vector2f& dir = movementProp->GetDirection();
				//... and update them.
				motorProp->Update(time, vel, dir);
			}
			// Update the Movement Property (this probably does nothing any more
			movementProp->Update(time, mousePos);
			
			if (positionProp->IsGrabbed() ) { // If being "held" by the mouse...
				// use the EMA velocity to set the direction in the movement property
				movementProp->SetDirection(mMouseEMAVelocity);	
				
			} else { // Not being held by mouse...
				sf::Vector2f position = positionProp->GetPosition();
				sf::Vector2f velocity = movementProp->GetVelocity();
				// Update the position of the object based on its current velocity
				position.x += velocity.x * time;
				position.y += velocity.y * time;
				//Check for bounces - move to a property??
				if (position.x < 0.f || position.x > 1280.f-25.f	) {
					velocity.x = -velocity.x;
				}
				if (position.y < 0.f || position.y > 720.f-25.f) {
					velocity.y = -velocity.y;
				}
				movementProp->SetDirection(velocity);//Update the direction vector in Movement Property.
				RestrictBoardBoundaries(position); // Prevent object moving outside board.
				// Friction - affects movement property. Only affected if not grabbed by mouse
				movementProp->ReduceSpeed(mFriction * time); 
			// Update position in Position Property.
			positionProp->SetPosition(position);
			}
		} // end of section requiring Movement property
		if( positionProp->IsGrabbed() ){
			//if grabbed
			sf::Vector2f position = positionProp->GetPosition();
			position += difference; // Update position based on how much mouse moved
			positionProp->SetPosition(position); // update position in Position Property.
		}
	} // end for
	// Record new mouse position
	mPreviousMousePosition = mousePos;
}

void SysMovement::OnClick(const sf::Vector2f& mousePos) {
	for (auto o : mRefObjects) {
		auto positionProp = o->GetProperty<ObjectPosition>(Property::Position);
		if (positionProp->OnClick(mousePos)) // if an object is grabbed, it doesn't check any more.
			break;
	}
	mPreviousMousePosition = mousePos;
}

void SysMovement::OnRelease() {
	for (auto o : mRefObjects) {
		auto positionProp = o->GetProperty<ObjectPosition>(Property::Position);
		if (positionProp == nullptr) continue;
		if (positionProp->IsGrabbed()) {
			auto movementProp = o->GetProperty<ObjectMovement>(Property::Move);
			if (movementProp == nullptr) continue;
			movementProp->SetVelocity(mMouseEMAVelocity);
			movementProp->SetDirection(mMouseEMAVelocity);
			positionProp->OnRelease();
			break;
		}
	}
}

void SysMovement::RestrictBoardBoundaries(sf::Vector2f& pos) {
	if (pos.x < 0.f) { pos.x = 0.f; }
	if (pos.y < 0.f) { pos.y = 0.f; }
	if (pos.x > 1280.f-25.f) {
		pos.x = 1280.f-25.f;
	}
	if (pos.y > 720.f-25.f) {
		pos.y = 720.f-25.f;
	}
}
void SysMovement::Render(sf::RenderWindow& window) {
	//txtBox.Render(window);
	for (auto o : mRefObjects) { // for each object
		auto movementProp = o->GetProperty<ObjectMovement>(Property::Move);
		if(movementProp != nullptr) movementProp->Render(window);
	}
}

sf::Vector2f SysMovement::ExpMovingAverageVelocity(double time, sf::Vector2f& currentVelocity ) {
	double alpha = 1 - std::exp(-time / 0.1);
	double newVelocityX = alpha * currentVelocity.x + (1 - alpha) * mMouseEMAVelocity.x;
	double newVelocityY = alpha * currentVelocity.y + (1 - alpha) * mMouseEMAVelocity.y;
	return sf::Vector2f(newVelocityX, newVelocityY);

}
