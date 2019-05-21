#include "App.h"

App::App() : mWindow("Whiteboard Prototype 1", sf::Vector2u(1280, 720))/*,
mEntityManager(&mSystemManager, &mTextureManager),
mStateManager(&mContext), mSoundManager(&mAudioManager),
mGUIManager(mWindow.GetEventManager(), &mContext)*/
{
	mClock.restart();
	srand((unsigned int)time(nullptr));

	//mSystemManager.SetEntityManager(&mEntityManager);
	//mContext.mWindow = &mWindow;
	//mContext.mEventManager = mWindow.GetEventManager();
	//mContext.mTextureManager = &mTextureManager;
	//mContext.mFontManager = &mFontManager;
	//mContext.mAudioManager = &mAudioManager;
	//mContext.mSoundManager = &mSoundManager;
	//mContext.mSystemManager = &mSystemManager;
	//mContext.mEntityManager = &mEntityManager;
	//mContext.mGUIManager = &mGUIManager;

	//mSystemManager.GetSystem<S_Sound>(System::Sound)->SetUp(&mAudioManager, &mSoundManager);

	////Debug:
	//mSystemManager.mDebugOverlay = &mContext.mDebugOverlay;

	//mFontManager.RequireResource("Main");

	//mStateManager.SwitchTo(StateType::Intro); // begin the App with this state
}

App::~App() {
	//mFontManager.ReleaseResource("Main");
}

sf::Time App::GetElapsed() { return mClock.getElapsedTime(); }
void App::RestartClock() { mElapsed = mClock.restart(); }
Window* App::GetWindow() { return &mWindow; }

void App::Update() {
	

	mWindow.Update(); // update window events
	if (mWindow.MouseClicked()) {
		mObjectManager.MouseClicked( static_cast<sf::Vector2f>( sf::Mouse::getPosition( *(mWindow.GetRenderWindow()) ) ) );
		mWindow.ClearMouseClick();
	}
	else if(mWindow.MouseReleased()) {
		mObjectManager.MouseReleased();
		mWindow.ClearMouseClick();
	}
	mObjectManager.Update(mElapsed.asSeconds(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(*(mWindow.GetRenderWindow()))));
	//mStateManager.Update(mElapsed);// update all states
	//mSoundManager.Update(mElapsed.asSeconds());
	//mContext.mGUIManager->Update(mElapsed.asSeconds());
	//GUI_Event guiEvent;
	//while (mContext.mGUIManager->PollEvent(guiEvent)) {
	//	mWindow.GetEventManager()->HandleEvent(guiEvent);
	//}
}

void App::Render() {
	mWindow.BeginDraw(); //Clear
	// Render here
	mBoard.Render(*mWindow.GetRenderWindow());
	mObjectManager.Render(*mWindow.GetRenderWindow());
	
	//mStateManager.Draw();
	sf::View CurrentView = mWindow.GetRenderWindow()->getView();
	mWindow.GetRenderWindow()->setView(mWindow.GetRenderWindow()->getDefaultView());
	//mContext.mGUIManager->Render(mWindow.GetRenderWindow());
	mWindow.GetRenderWindow()->setView(CurrentView);


	mWindow.EndDraw(); // Display
}

void App::LateUpdate() {
	//mStateManager.ProcessRequests(); // remove states no longer required
	RestartClock();
}