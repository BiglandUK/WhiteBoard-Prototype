#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
//#include "EventManager.h"

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw(); //Clear the window
	void EndDraw(); //Display the changes

	void Update();

	bool IsDone();
	bool IsFullscreen();
	bool IsFocused();
	bool MouseClicked();
	bool MouseReleased();
	void ClearMouseClick();

	//void ToggleFullscreen(EventDetails* details);
	//void Close(EventDetails* details = nullptr);

	sf::RenderWindow* GetRenderWindow();
	//EventManager* GetEventManager();
	sf::Vector2u GetWindowSize();
	sf::FloatRect GetViewSpace();

private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();

	sf::RenderWindow mWindow;
	//EventManager mEventManager;
	sf::Vector2u mWindowSize;
	std::string mWindowTitle;
	bool mIsDone;
	bool mIsFullscreen;
	bool mIsFocused;
	bool mMouseClicked;
	bool mMouseReleased;
};