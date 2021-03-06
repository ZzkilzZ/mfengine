#include "MenuState.hpp"

MenuState::MenuState(mf::Window *tWindow):
mEventHandler(tWindow),
mContainer(tWindow),
mPlayButton(tWindow, &mResourceManager),
mOptionsButton(tWindow, &mResourceManager),
mQuitButton(tWindow, &mResourceManager),
mTitle(tWindow, &mResourceManager, &mEventHandler),
mContainerOptions(tWindow),
mFullScreenButton(tWindow, &mResourceManager),
mBackButton(tWindow, &mResourceManager)
{
	mWindow = tWindow;
	mState = MENU_STATE::MAIN;
	mReturn = ReturnCtrl::END;
	mRunning = true;
	mDeltaTime = 1.f / 32.f;
	mWindow->setMouseCursorVisible(true);

	mContainer.AddItem(&mTitle);
	mTitle.SetPosition(sf::Vector2f(520, 150));
	mTitle.SetSize(880, 100);
	mTitle.SetFontSize(70);
	mTitle.SetAllowFocus(false);
	mTitle.SetText("An MFENGINE demo");
	mTitle.SetFontColor(sf::Color::Red);
	mTitle.SetTextPosition(sf::Vector2f(15, 5));
	mTitle.SetBackground(sf::Color(0x351f1fff));

	initMenuButtons();
}

MenuState::~MenuState()
{
	
}

void				MenuState::update()
{
	mWindow->update();

	switch (mState)
	{
	case MENU_STATE::MAIN:
		mContainer.Update();
		updateMain();
		break;
	case MENU_STATE::OPTIONS:
		mContainerOptions.Update();
		updateOptions();
		break;
	default:
		break;
	}
}

void			MenuState::updateMain()
{
	if (mQuitButton.GetState() == mf::MouseState::CLICKED)
	{
		mReturn = ReturnCtrl::END;
		mRunning = false;
	} else
	if (mPlayButton.GetState() == mf::MouseState::CLICKED)
	{
		mReturn = ReturnCtrl::GAME;
		mRunning = false;
	} else
	if (mOptionsButton.GetState() == mf::MouseState::CLICKED)
	{
		mState = MENU_STATE::OPTIONS;
	}
}

void			MenuState::updateOptions()
{
	if (mFullScreenButton.GetState() == mf::MouseState::CLICKED)
	{
		mWindow->toggleFullscreen();
		mFullScreenButton.SetText((mWindow->isFullscreen()) ? "Windowed" : "Fullscreen");
	} else
	if (mBackButton.GetState() == mf::MouseState::CLICKED)
		mState = MENU_STATE::MAIN;
}

void				MenuState::handle_events()
{
	mEventHandler.HandleEvents();
}

void				MenuState::render()
{
	mWindow->clear(sf::Color(50, 100, 0, 50));
	mWindow->pushGLStates();
	glBindBuffer(GL_ARRAY_BUFFER,0);
    glDisableVertexArrayAttribEXT(0,0);
	mWindow->resetGLStates();
	switch (mState)
	{
	case MENU_STATE::MAIN:
		mContainer.Draw();
		break;
	case MENU_STATE::OPTIONS:
		mContainerOptions.Draw();
		break;
	}
	mWindow->popGLStates();
	mWindow->display();
}

void				MenuState::initMenuButtons()
{
	//MAIN
	mContainer.AddItem(&mPlayButton);
	mContainer.SetPosition(sf::Vector2f(850, 400));
	mContainer.SetSize(sf::Vector2f(500, 800));
	mPlayButton.SetPosition(sf::Vector2f(0, 0));
	mPlayButton.SetScale(sf::Vector2f(8, 5));
	mPlayButton.SetFont("assets/fonts/pdark.ttf");
	mPlayButton.SetText("PLAY");
	mPlayButton.SetTextOffset(sf::Vector2f(50, 20));
	mContainer.AddItem(&mOptionsButton);
	mOptionsButton.SetPosition(sf::Vector2f(0, 100));
	mOptionsButton.SetScale(sf::Vector2f(8, 5));
	mOptionsButton.SetFont("assets/fonts/pdark.ttf");
	mOptionsButton.SetText("Options");
	mOptionsButton.SetTextOffset(sf::Vector2f(30, 20));
	mContainer.AddItem(&mQuitButton);
	mQuitButton.SetPosition(sf::Vector2f(0, 200));
	mQuitButton.SetScale(sf::Vector2f(8, 5));
	mQuitButton.SetFont("assets/fonts/pdark.ttf");
	mQuitButton.SetText("QUIT");
	mQuitButton.SetTextOffset(sf::Vector2f(50, 20));

	//OPTIONS
	mContainerOptions.AddItem(&mFullScreenButton);
	mContainerOptions.SetSize(sf::Vector2f(1920, 1080));
	mFullScreenButton.SetPosition(sf::Vector2f(850, 400));
	mFullScreenButton.SetScale(sf::Vector2f(8, 5));
	mFullScreenButton.SetFont("assets/fonts/pdark.ttf");
	mFullScreenButton.SetText("Fullscreen");
	mFullScreenButton.SetTextOffset(sf::Vector2f(50, 20));
	mFullScreenButton.SetTextSize(20);
	mContainerOptions.AddItem(&mBackButton);
	mBackButton.SetPosition(sf::Vector2f(250, 100));
	mBackButton.SetScale(sf::Vector2f(8, 5));
	mBackButton.SetFont("assets/fonts/pdark.ttf");
	mBackButton.SetText("Back");
	mBackButton.SetTextOffset(sf::Vector2f(50, 20));
	mBackButton.SetTextSize(20);

	mContainer.Update();
	mContainerOptions.Update();
}