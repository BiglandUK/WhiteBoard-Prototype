#pragma once
#include "Window.h"
#include "ObjectManager.h"
#include "Board.h"
//#include "FontManager.h"
//#include "EventManager.h"
//#include "GUI_Manager.h"
//#include "StateManager.h"
//#include "TextureManager.h"

#include <iostream>

class App {
public:
	App();
	~App();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();

	Window* GetWindow();

private:
	void RestartClock();

	sf::Clock mClock;
	sf::Time mElapsed;

	Window mWindow;

	ObjectManager mObjectManager;
	Board mBoard;
	//SharedContext mContext; // holds pointers to the managers, window, Appmap
	//
	//SystemManager mSystemManager; // manages animation, collision, movement, etc.
	//FontManager mFontManager;
	//AudioManager mAudioManager;
	//SoundManager mSoundManager;
	//EntityManager mEntityManager; // manages player, enemies, objects, etc.
	//GUI_Manager mGUIManager;
	//TextureManager mTextureManager; // manages sprite graphics, etc.
	//StateManager mStateManager; // manages states (of App, entities, etc.) This is the main manager for the Update and Draw routines.
};