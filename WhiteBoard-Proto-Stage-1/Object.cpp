#include "Object.h"
#include "PropulsionMotor.h"
Object::Object()
	:mVisible(true)
{
	mProperties.emplace(Property::Position, std::make_shared<ObjectPosition>(0.f, 0.f));
	mProperties.emplace(Property::Move, std::make_shared<ObjectMovement>());

}

Object::Object(float x, float y, bool move)
	: mVisible(true), mFillColour(sf::Color::Red)
{
	mProperties.emplace(Property::Position, std::make_shared<ObjectPosition>(x, y)); //new ObjectPosition(x, y));
	if (move)
		mProperties.emplace(Property::Move, std::make_shared<ObjectMovement>());// new ObjectMovement());
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


void Object::Render(sf::RenderWindow& window) {
	//ObjectPosition* obj = static_cast<ObjectPosition*>(mProperties.find(Property::Position)->second);

	std::shared_ptr<ObjectPosition> obj = GetProperty<ObjectPosition>(Property::Position);
	if (obj == nullptr)return;
	mCircle.setPosition(obj->GetPosition().x, obj->GetPosition().y);
	mCircle.setOrigin(obj->GetOrigin());
	mCircle.setFillColor(mFillColour);
	mCircle.setRadius(25.f);

	window.draw(mCircle);
}

void Object::AddMotor() {
	AddProperty<PropulsionMotor>(Property::Motor);
}