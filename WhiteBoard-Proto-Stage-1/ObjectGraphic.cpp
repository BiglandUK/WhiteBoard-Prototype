#include "ObjectGraphic.h"

// VectorCircle
VectorCircle::VectorCircle(float radius, const sf::Color& colour)
	: mRadius(radius), mFillColour(colour)
{}

GraphicType VectorCircle::GetType() const { return GraphicType::Vector; }

void VectorCircle::Render(Object& object, sf::RenderWindow& window) {
	//ObjectPosition* obj = static_cast<ObjectPosition*>(mProperties.find(Property::Position)->second);
	sf::CircleShape mCircle;
	std::shared_ptr<ObjectPosition> obj = object.GetProperty<ObjectPosition>(Property::Position);
	if (obj == nullptr)return;
	mCircle.setPosition(obj->GetPosition().x, obj->GetPosition().y);
	mCircle.setOrigin(obj->GetOrigin());
	mCircle.setFillColor(mFillColour);
	mCircle.setRadius(mRadius);

	window.draw(mCircle);
}

float VectorCircle::GetRadius() const {
	return mRadius;
}

void VectorCircle::SetRadius(float radius) {
	mRadius = radius;
}

sf::Color VectorCircle::GetColour() const {
	return mFillColour;
}

void VectorCircle::SetColour(const sf::Color& colour) {
	mFillColour = colour;
}

// VectorPolygon

VectorPolygon::VectorPolygon(float width, float height, const sf::Color colour)
	: mWidth(width), mHeight(height), mFillColour(colour)
{}

GraphicType VectorPolygon::GetType() const {
	return GraphicType::Vector;
}

void VectorPolygon::Render(Object& object, sf::RenderWindow& window) {
	//ObjectPosition* obj = static_cast<ObjectPosition*>(mProperties.find(Property::Position)->second);
	sf::RectangleShape rect;
	std::shared_ptr<ObjectPosition> obj = object.GetProperty<ObjectPosition>(Property::Position);
	if (obj == nullptr)return;
	rect.setPosition(obj->GetPosition().x, obj->GetPosition().y);
	rect.setOrigin(obj->GetOrigin());
	rect.setFillColor(mFillColour);
	rect.setSize(sf::Vector2f(mWidth, mHeight));

	window.draw(rect);
}


//Text Graphic
TextGraphic::TextGraphic(std::string text)
:mText(text)
{}

GraphicType TextGraphic::GetType() const {	return GraphicType::Text; }

void TextGraphic::Render(Object& object, sf::RenderWindow& window) {
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text(mText, font);
	std::shared_ptr<ObjectPosition> obj = object.GetProperty<ObjectPosition>(Property::Position);
	if (obj == nullptr)return;
	text.setPosition(obj->GetPosition().x, obj->GetPosition().y);
	window.draw(text);
}