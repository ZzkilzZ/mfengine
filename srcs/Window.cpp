#include "Window.hpp"

namespace mf
{

Window::Window():
mSize(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT),
mTitle("Default Window Title")
{
	create();
}

Window::Window(std::string &tTitle, sf::Vector2i tSize):
mSize(tSize),
mTitle(tTitle)
{
	create();
}

Window::~Window()
{
	destroy();
}

bool	Window::create()
{
	sf::VideoMode mode(mSize.x, mSize.y);

	if (mIsFullscreen && !mode.isValid())
		mode = sf::VideoMode::getFullscreenModes().front();
	mWindow.create(mode, mTitle,
		(mIsFullscreen) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	initOpengl();
	return (true);
}

void	Window::initOpengl()
{
	glewExperimental = GL_TRUE; 
	glewInit();
	glEnable(GL_TEXTURE_2D);
}

void	Window::destroy()
{
	mWindow.close();
}

void	Window::processEvents()
{
	sf::Event	event;

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			destroy();
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F11)
			toggleFullscreen();
	}
}

void	Window::update()
{
	processEvents();
}

void	Window::toggleFullscreen()
{
	mIsFullscreen = !mIsFullscreen;
	destroy();
	create();
}

void	Window::clear()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	Window::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	Window::clear(sf::Color color)
{
	glClearColor(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	Window::draw(sf::Drawable *tDrawable)
{
	mWindow.draw(*tDrawable);
}

void	Window::display()
{
	mWindow.display();
}

}
