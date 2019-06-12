#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectProperty.h"
#include <unordered_map>
#include <memory>

class ObjectGraphic;

using PropertyList = std::unordered_map<Property, std::shared_ptr<ObjectProperty>>;

class Object {
private:
	bool mVisible;
	sf::Color mFillColour;
	PropertyList mProperties;

	sf::CircleShape mCircle;
	ObjectGraphic* mGraphic;

public:
	Object();
	Object(float x, float y, bool move = true);
	~Object();

	template<class T>
	bool AddProperty(Property propertyType) {
		mProperties.emplace(propertyType, std::make_shared<T>());
		return true;
	}

	void SetFillColour(const sf::Color& colour);

	bool IsVisible() const;
	void ToggleVisibility();

	//std::shared_ptr<ObjectProperty> GetProperty(const Property& prop);

	
	template<class T>
		std::shared_ptr<T> GetProperty(const Property& propType) {
			auto property = mProperties.find(propType);
			if (property == mProperties.end()) return nullptr;
			return std::static_pointer_cast<T>(property->second);	
	}


	void SetGraphic(ObjectGraphic* graphic);
	void Render(sf::RenderWindow& window);

	void AddMotor();
};