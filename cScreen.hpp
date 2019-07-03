#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


class cScreen
{
public:
	virtual int Run(sf::RenderWindow &app) = 0;
};
