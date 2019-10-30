#include "MenuState.hpp"

MenuState::MenuState(mf::Window *tWindow):
mContainer(tWindow),
mPlayButton(tWindow, &mResourceManager),
mOptionsButton(tWindow, &mResourceManager),
mQuitButton(tWindow, &mResourceManager),
mOptionsContainer(tWindow)
{
	mWindow = tWindow;
	initButtons();
}

MenuState::~MenuState()
{
	
}

MenuState::ReturnCtrl	MenuState::run()
{
	sf::Time	elapsedTime;

	mRunning = true;
	elapsedTime = sf::seconds(MENUDELTATIME);
	while (mRunning  && mWindow->isOpen())
	{
		while (elapsedTime.asSeconds() > MENUDELTATIME)
		{
			handle_events();
			update();
			elapsedTime -= sf::seconds(MENUDELTATIME);
		}
		render();
		elapsedTime += mGameLoop.restart();
	}
	return (mReturn);
}

void				MenuState::update()
{
	mWindow->update();
	mContainer.Update();

	if (mQuitButton.GetState() == mf::MouseState::CLICKED)
	{
		mReturn = ReturnCtrl::END;
		mRunning = false;
	}
	if (mPlayButton.GetState() == mf::MouseState::CLICKED)
	{
		mReturn = ReturnCtrl::GAME;
		mRunning = false;
	}
}

void				MenuState::handle_events()
{
	
}

void				MenuState::render()
{
	mWindow->clear(sf::Color::Green);

	mContainer.Draw();

	mWindow->display();
}

void				MenuState::initButtons()
{
	mPlayButton.SetPosition(sf::Vector2f(850, 400));
	mPlayButton.SetScale(sf::Vector2f(8, 5));
	mPlayButton.SetFont("assets/fonts/pdark.ttf");
	mPlayButton.SetText("PLAY");
	mPlayButton.SetTextOffset(sf::Vector2f(50, 20));
	mContainer.AddItem(&mPlayButton);
	mOptionsButton.SetPosition(sf::Vector2f(850, 500));
	mOptionsButton.SetScale(sf::Vector2f(8, 5));
	mOptionsButton.SetFont("assets/fonts/pdark.ttf");
	mOptionsButton.SetText("Options");
	mOptionsButton.SetTextOffset(sf::Vector2f(30, 20));
	mContainer.AddItem(&mOptionsButton);
	mQuitButton.SetPosition(sf::Vector2f(850, 600));
	mQuitButton.SetScale(sf::Vector2f(8, 5));
	mQuitButton.SetFont("assets/fonts/pdark.ttf");
	mQuitButton.SetText("QUIT");
	mQuitButton.SetTextOffset(sf::Vector2f(50, 20));
	mContainer.AddItem(&mQuitButton);
}