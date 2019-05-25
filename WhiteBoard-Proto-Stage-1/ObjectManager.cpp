#include "ObjectManager.h"
#include "PropulsionMotor.h"

ObjectManager::ObjectManager() 
	:systemMovement(mObjects)
{
	mObjects.push_back(std::make_shared<Object>(Object(0.f, 0.f))); mObjects[0]->SetFillColour(sf::Color::Red);

	mObjects.push_back(std::make_shared<Object>(Object(1000.f, 500.f))); mObjects[1]->SetFillColour(sf::Color::Yellow);
	mObjects[1]->AddMotor();
	mObjects[1]->GetProperty<ObjectMovement>(Property::Move)->SetBounce(false);
	std::shared_ptr<PropulsionMotor> pm = mObjects[1]->GetProperty<PropulsionMotor>(Property::Motor);
	pm->SetAcceleration(500.f);
	pm->ChangeType(PropulsionMotor::Type::Constant);
	pm->SetSpeed(400.0f);

	mObjects.push_back(std::make_shared<Object>(Object(250.f, 300.f))); mObjects[2]->SetFillColour(sf::Color::Green); //mObjects[2]->ToggleVisibility();
	mObjects[2]->AddMotor();
	std::shared_ptr<PropulsionMotor> pm3 = mObjects[2]->GetProperty<PropulsionMotor>(Property::Motor);
	pm3->SetSpeed(400.0f);
	pm3->SetAcceleration(40.f);
	pm3->ChangeType(PropulsionMotor::Type::Constant);

	
	mObjects.push_back(std::make_shared<Object>(Object(700.f, 25.f))); mObjects[3]->SetFillColour(sf::Color::Blue);
	mObjects[3]->AddMotor();
	std::shared_ptr<PropulsionMotor> pm2 = mObjects[3]->GetProperty<PropulsionMotor>(Property::Motor);
	pm2->SetSpeed(400.0f);
	pm2->ChangeType(PropulsionMotor::Type::TimePulse);
	pm2->SetRunningDuration(2.5f);
	pm2->SetIdleDuration(4.5f);

}

void ObjectManager::MouseClicked(const sf::Vector2f& mousePos) {
	systemMovement.OnClick(mousePos);
}

void ObjectManager::MouseReleased() {
	systemMovement.OnRelease();
}

void ObjectManager::Update(float time, const sf::Vector2f& mousePos) {
	
	systemMovement.Update(time, mousePos);
}

void ObjectManager::Render(sf::RenderWindow& window){
	for (auto o : mObjects) {
		if (o->IsVisible()) {
			o->Render(window);
		}
	}
	systemMovement.Render(window);
}

