#pragma once
#include "cScreen.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class MainMenu : public cScreen
{
	int menuCurent = 0;

	public:
		MainMenu();
		int Run(sf::RenderWindow& app);
};
