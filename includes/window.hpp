#pragma once

# include <SFML/Graphics.hpp>
# include <SFML/OpenGL.hpp>

# define DEFAULT_WIN_HEIGHT		1080
# define DEFAULT_WIN_WIDTH		1920

class window
{
private:
	sf::RenderWindow	mWindow;
	sf::Vector2i		mSize;
	std::string			mTitle;
	bool				mIsFullscreen = false;

	bool				create();
	void				destroy();
	void				initOpengl();
	void				processEvents();

	
public:
	window();
	window(std::string title, sf::Vector2i size);
	~window();
	
	void				update();
	void				toggleFullscreen();
	void				clear();
	void				clear(sf::Color color);
	void				clear(float r, float g, float b, float a);
	void				display();

	bool				isOpen(){return (mWindow.isOpen());};
};