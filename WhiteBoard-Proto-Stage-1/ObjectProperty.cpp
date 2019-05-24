#include "ObjectProperty.h"
#include "SFML/Graphics/Rect.hpp"

ObjectProperty::ObjectProperty(const Property& type, bool canRemove, bool canDisable)
	:mPropertyType(type), mCanRemove(canRemove), mCanDisable(canDisable)
{}

Property ObjectProperty::GetType() {
	return mPropertyType;
}

// OBJECT POSITION
ObjectPosition::ObjectPosition(float x, float y)
	: ObjectProperty(Property::Position),
	mPosition(sf::Vector2f(x,y)), mGrabbed(false)
{}

void ObjectPosition::SetPosition(float x, float y) {
	SetPosition(sf::Vector2f(x, y));
}

void ObjectPosition::SetPosition(const sf::Vector2f& position) {
	mPosition = position;
}

sf::Vector2f ObjectPosition::GetPosition()const {
	return mPosition;
}

void ObjectPosition::SetOrigin(const sf::Vector2f& origin) {
	mOrigin = origin;
}

sf::Vector2f ObjectPosition::GetOrigin()const {
	return mOrigin;
}

bool ObjectPosition::OnClick(const sf::Vector2f& mousePos) {
	if (!mGrabbed && IsInside(mousePos)) {
		mGrabbed = true;
		mPreviousMousePosition = mousePos;
		return true;
	}
	return false;
}

void ObjectPosition::OnRelease() {
	mGrabbed = false;
}

bool ObjectPosition::IsGrabbed() const {
	return mGrabbed;
}

void ObjectPosition::Update(float time, const sf::Vector2f& mousePos) {
	if (mGrabbed) {		
		sf::Vector2f difference(mPosition.x - mousePos.x, mPosition.y - mousePos.y);
		mPosition += difference;
		mPreviousMousePosition = mousePos;
	}
}

// TODO: use some form of Origin - also, adapt to any shape. Need a Zone object.
bool ObjectPosition::IsInside(const sf::Vector2f& mousePos) {
	auto rect = sf::FloatRect(mPosition.x, mPosition.y, 50.f, 50.f);
	return rect.contains(mousePos);
	// IsInside would have to be placed elsewhere, to allow the details of the object to be available for such collision checking.
}

// OBJECT MOVEMENT
ObjectMovement::ObjectMovement()
	:ObjectProperty(Property::Move), mGrabbed(false)
{
	mMaxVelocityMagnitude = 500.f;
	mDirection.x = 1.f; mDirection.y = 0.f;
	txtBox.Setup(5, 14, 400, sf::Vector2f(50.0f, 0.f));
}

ObjectMovement::~ObjectMovement() {

}

void ObjectMovement::SetDirection(const sf::Vector2f& direction) {
	// Check if the vector is valid - a zero vector, one with no magnitude, is not valid.
	if (direction.x == 0.f && direction.y == 0)
		return;

	// Normalise vector passed in.
	float magnitude = std::hypotf(direction.x, direction.y);
	mDirection.x = direction.x / magnitude;
	mDirection.y = direction.y / magnitude;
	
}

const sf::Vector2f& ObjectMovement::GetDirection() const {
	return mDirection;
}

sf::Vector2f& ObjectMovement::GetDirection() {
	return mDirection;
}

void ObjectMovement::SetVelocity(const sf::Vector2f& velocity) {
	mActualVelocity = velocity;
}

const sf::Vector2f& ObjectMovement::GetVelocity() const {
	return mActualVelocity;
}

sf::Vector2f& ObjectMovement::GetVelocity() {
	return mActualVelocity;
}

void ObjectMovement::ReduceSpeed(const float speed) {
	if (IsStopped()) return;
	float mag = std::hypotf(mActualVelocity.x, mActualVelocity.y);
	float newSpeed = mag - speed;
	if (newSpeed < 0.f) newSpeed = 0.f; //Avoid negative speeds
	mActualVelocity.x = mDirection.x * newSpeed;
	mActualVelocity.y = mDirection.y * newSpeed;
}

bool ObjectMovement::IsStopped()const {
	return mActualVelocity.x == 0.f && mActualVelocity.y == 0.f;
}

void ObjectMovement::OnRelease() {

}

void ObjectMovement::Update(float time, const sf::Vector2f& mousePos) {
}

void ObjectMovement::Render(sf::RenderWindow& window) {
	txtBox.Render(window);
}

void ObjectMovement::SetBounce(bool bounce){
	mBounce = bounce;
}

bool ObjectMovement::DoesBounce()const{
	return mBounce;
}
