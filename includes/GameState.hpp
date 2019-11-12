#pragma once

#include "ScreenState.hpp"
#include "ResourceManager.hpp"
#include "Terrain.hpp"
#include "Player.hpp"
#include "Camera.hpp"

#include <math.h>

#define DELTATIME		1.f/64.f

class GameState : public mf::ScreenState
{
private:
	mf::ResourceManager		mResourceManager;
	mf::EventHandler		mEventHandler;
	mf::Camera				mCamera;
	mf::Terrain				terrain;
	mf::Player				mPlayer;

public:
	explicit GameState(mf::Window *tWindow);
	~GameState();

	mf::ScreenState::ReturnCtrl		run();
	void							update();
	void							handle_events();
	void							render();
};
