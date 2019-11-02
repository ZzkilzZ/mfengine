#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace mf
{
	class ResourceManager
	{
	private:
		std::map<std::string, sf::Font>		mFonts;
		std::map<std::string, sf::Image>	mImages;
		std::map<std::string, sf::Shader*>	mShaders;
		
	public:
		static bool						verbose;

		ResourceManager();
		~ResourceManager();

		sf::Image		LoadImage(std::string path);
		sf::Font		LoadFont(std::string path);
		void			LoadShader(std::string name, std::string vertex, std::string fragment);

		void			BindShader(std::string name);
	};
}