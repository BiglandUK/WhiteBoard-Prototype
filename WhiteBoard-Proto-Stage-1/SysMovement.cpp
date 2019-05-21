#include "SysMovement.h"

SysMovement::SysMovement(Objects& objects)
	: mRefObjects(objects), mFriction(40.f)
{
}

void SysMovement::Update(float time, const sf::Vector2f& mousePos) {

	sf::Vector2f difference = static_cast<sf::Vector2f>(mousePos) - mPreviousMousePosition;

	sf::Vector2f velocity;
	if (time > 0.f) { velocity = sf::Vector2f(difference.x / time, difference.y / time); }
	mMouseEMAVelocity = ExpMovingAverageVelocity(time, velocity);
	for (auto o : mRefObjects) { // for each object
		if (!(o->IsVisible())) { continue; } // ignore invisible objects
		auto movementProp = o->GetProperty<ObjectMovement>(Property::Move);//std::static_pointer_cast<ObjectMovement>(o->GetProperty(Property::Move));
		if (movementProp == nullptr)return;
		movementProp->Update(time, mousePos);
		auto positionProp = o->GetProperty<ObjectPosition>(Property::Position);
		if (positionProp == nullptr)return;
		if (positionProp->IsGrabbed() ) {
			//movementProp->SetVelocity(mMouseEMAVelocity);
			movementProp->SetDirection(mMouseEMAVelocity);
			//Update object position
			sf::Vector2f position = positionProp->GetPosition();
			position += difference;
			positionProp->SetPosition(position);
		}
		else {
			// use velocity to calculate new object position
			sf::Vector2f position = positionProp->GetPosition();
			sf::Vector2f velocity = movementProp->GetVelocity();

			position.x += velocity.x * time;
			position.y += velocity.y * time;
			//Check for bounces
			if (position.x < 0.f || position.x > 1280.f-25.f	) {
				velocity.x = -velocity.x;
			}
			if (position.y < 0.f || position.y > 720.f-25.f) {
				velocity.y = -velocity.y;
			}
			movementProp->SetDirection(velocity);
			RestrictBoardBoundaries(position);
			// Friction
			movementProp->ReduceSpeed(mFriction * time);
			//Update
			positionProp->SetPosition(position);
		}
	}

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