#pragma once
#include "Object.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include "SysMovement.h"

using Objects = std::vector<std::shared_ptr<Object>>;

class ObjectManager {
public:
	ObjectManager();

	void Render(sf::RenderWindow& window);

	void MouseClicked(const sf::Vector2f& mousePos);
	void MouseReleased();

	void Update(float time, const sf::Vector2f& mousePos);

private:
	Objects mObjects;
	SysMovement systemMovement;
};