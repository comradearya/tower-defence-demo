#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu() {}////////////////////////////////////////////////////////////////


int MainMenu::Run(sf::RenderWindow &app)
{
	sf::Event	evnt;
	sf::Font	font;
	sf::Text	menu[3];
	std::string menuText[] = { "Play", "Levels", "Exit" };

	int menuCount = 3;
	

	if (!font.loadFromFile("verdanab.ttf"))
	{
		std::cerr << "Error load font verdanab.ttf";
		return -1;
	}

	for (int i = 0; i < menuCount; ++i)
	{
		menu[i].setFont(font);
		menu[i].setString(menuText[i]);
		menu[i].setCharacterSize(29);
		menu[i].setPosition({ 350.0, (float)(100 + 80 * i) });
		menu[i].setFillColor(sf::Color(255, 255, 255, 255));
	}
	menu[menuCurent].setFillColor(sf::Color(255, 0, 0, 255));

	while (true)
	{
		while (app.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				return -1;

			if (evnt.type == sf::Event::KeyPressed)
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up:
					if (menuCurent > 0)
					{
						menu[menuCurent].setFillColor(sf::Color(255, 255, 255, 255));
						menu[menuCurent-1].setFillColor(sf::Color(255, 0, 0, 255));
						--menuCurent;
					}
					break;
				case sf::Keyboard::Down:
					if (menuCurent < menuCount-1)
					{
						menu[menuCurent].setFillColor(sf::Color(255, 255, 255, 255));
						menu[menuCurent + 1].setFillColor(sf::Color(255, 0, 0, 255));
						++menuCurent;
					}
					break;
				case sf::Keyboard::Return:
					switch(menuCurent)
					{
					case 0:
						return 2;
					case 1:
						return 1;
					case 2:
						return -1;
					}
				default:
					break;
				}
		}

		app.clear(sf::Color(50, 0, 150, 255));
		for (int i = 0; i < menuCount; ++i)
		{
			app.draw(menu[i]);
		}
		app.display();
	}


	return -1;
}