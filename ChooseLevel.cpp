
#include <iostream>
#include "ChooseLevel.hpp"

ChooseLevel::ChooseLevel() {}


int ChooseLevel::Run(sf::RenderWindow &app)
{
    sf::Event	evnt;
	sf::Font	font;
	sf::Text	ltext[6];
	std::string levelText[6] = { "Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Exit" };

	int levelCount = 6;
	int levelCurent = 0;

	if (!font.loadFromFile("verdanab.ttf"))
	{
		std::cerr << "Error load font verdanab.ttf";
		return -1;
	}
    for (int i = 0; i < levelCount; ++i)
	{
		ltext[i].setFont(font);
		ltext[i].setString(levelText[i]);
		ltext[i].setCharacterSize(29);
		ltext[i].setPosition({ 330.0, (float)(50 + 80 * i) });
		ltext[i].setFillColor(sf::Color(255, 255, 255, 255));
	}
	ltext[levelCurent].setFillColor(sf::Color(255, 0, 0, 255));

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
					if (levelCount > 0)
					{
						ltext[levelCurent].setFillColor(sf::Color(255, 255, 255, 255));
						ltext[levelCurent-1].setFillColor(sf::Color(255, 0, 0, 255));
						--levelCurent;
					}
					break;
				case sf::Keyboard::Down:
					if (levelCurent < levelCount-1)
					{
						ltext[levelCurent].setFillColor(sf::Color(255, 255, 255, 255));
						ltext[levelCurent + 1].setFillColor(sf::Color(255, 0, 0, 255));
						++levelCurent;
					}
					break;
				case sf::Keyboard::Return:
					switch(levelCurent)
					{
					case 0:
						return 2;
					case 1:
						return 3;
					case 2:
						return 4;
					case 3:
						return 5;
					case 4:
						return 6;
					case 5:
						return -1;
					}
				default:
					break;
				}
		}

		app.clear(sf::Color(50, 0, 150, 255));
		for (int i = 0; i < levelCount; ++i)
		{
			app.draw(ltext[i]);
		}
		app.display();
	}
}