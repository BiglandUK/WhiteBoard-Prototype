#include "Window.h"

Window::Window() { Setup("Window", sf::Vector2u(640, 480)); }

Window::Window(const std::string& title, const sf::Vector2u& size)
{
	Setup(title, size);
	mMouseClicked = false;
}

Window::~Window() {
	mWindow.close();
}

void Window::Setup(const std::string& title, const sf::Vector2u& size)
{
	mWindowTitle = title;
	mWindowSize = size;
	mIsFullscreen = false;
	mIsDone = false;
	mIsFocused = true; // Default value for focused flag.

	/*mEventManager.AddCallback(StateType(0), "Fullscreen_toggle",
		&Window::ToggleFullscreen, this);
	mEventManager.AddCallback(StateType(0), "Window_close",
		&Window::Close, this);*/

	Create();
}

void Window::Create() {
	/*auto style = (mIsFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	mWindow.create({ mWindowSize.x, mWindowSize.y, 32 }, mWindowTitle, style);*/

	sf::Uint32 style = sf::Style::Default;
	if (mIsFullscreen) { style = sf::Style::Fullscreen; }

	mWindow.create(sf::VideoMode(mWindowSize.x, mWindowSize.y, 32), mWindowTitle, style);
	mWindow.clear(sf::Color::Black);
}

void	Window::BeginDraw() { mWindow.clear(sf::Color::Black); }// (240, 240, 240, 0)); }
void	Window::EndDraw() { mWindow.display(); }

bool	Window::IsDone() { return mIsDone; }
bool	Window::IsFullscreen() { return mIsFullscreen; }
bool	Window::IsFocused() { return mIsFocused; }
bool	Window::MouseClicked() { return mMouseClicked; }
bool	Window::MouseReleased() { return mMouseReleased; }
void	Window::ClearMouseClick() { mMouseClicked = false; mMouseReleased = false; }

sf::RenderWindow*	Window::GetRenderWindow() { return &mWindow; }
//EventManager*		Window::GetEventManager() { return &mEventManager; }
sf::Vector2u		Window::GetWindowSize() { return mWindowSize; }

sf::FloatRect		Window::GetViewSpace() {
	sf::Vector2f viewCentre = mWindow.getView().getCenter();
	sf::Vector2f viewSize = mWindow.getView().getSize();
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCentre - viewSizeHalf, viewSize);
	return viewSpace;
}

//void Window::ToggleFullscreen(EventDetails* details) {
//	mIsFullscreen = !mIsFullscreen;
//	mWindow.close();
//	Create();
//}

//void	Window::Close(EventDetails* details) { mIsDone = true; }

void Window::Update() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			mIsFocused = false;
			//mEventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			mIsFocused = true;
			//mEventManager.SetFocus(true);
		}
		else if (event.type == sf::Event::Closed) {
			mIsDone = true;
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			mMouseClicked = true;
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			mMouseReleased = true;
			}
		//mEventManager.HandleEvent(event);
	}
	//mEventManager.Update();
}