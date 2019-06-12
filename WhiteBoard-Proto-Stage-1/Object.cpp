#include "Object.h"
#include "PropulsionMotor.h"
#include "ObjectGraphic.h"

Object::Object()
	:mVisible(true), mGraphic(nullptr)
{
	mProperties.emplace(Property::Position, std::make_shared<ObjectPosition>(0.f, 0.f));
	mProperties.emplace(Property::Move, std::make_shared<ObjectMovement>());

	mGraphic = new VectorCircle(25.f, sf::Color::Cyan);
}

Object::Object(float x, float y, bool move)
	: mVisible(true), mGraphic(nullptr)
{
	mProperties.emplace(Property::Position, std::make_shared<ObjectPosition>(x, y)); //new ObjectPosition(x, y));
	if (move)
		mProperties.emplace(Property::Move, std::make_shared<ObjectMovement>());// new ObjectMovement());

	mGraphic = new VectorCircle(25.f, sf::Color::Cyan);
}

Object::~Object() {
	if (mGraphic) delete mGraphic;
}

bool Object::IsVisible()const {
	return mVisible;
}

void Object::ToggleVisibility() {
	mVisible = !mVisible;
}

void Object::SetFillColour(const sf::Color& colour) {
	mFillColour = colour;
}

void Object::SetGraphic(ObjectGraphic* graphic) {
	if (graphic == nullptr)return;
	mGraphic = graphic;
}

void Object::Render(sf::RenderWindow& window) {
	if (mGraphic)
		mGraphic->Render(*this, window);
}

void Object::AddMotor() {
	AddProperty<PropulsionMotor>(Property::Motor);
}