#pragma once

#include "Window.hpp"

namespace mf
{

class ScreenState
{
public:
	enum class ReturnCtrl{
		END,
		GAME,
		MENU,
		OPTIONS
	};

	virtual ~ScreenState(){}
	virtual ReturnCtrl	run() = 0;
	virtual void		update() = 0;
	virtual void		handle_events() = 0;
	virtual void		render() = 0;
	
protected:
	sf::Clock		mGameLoop;
	Window			*mWindow;
	bool			mRunning = true;
	ReturnCtrl		mReturn = ReturnCtrl::END;
};

}
