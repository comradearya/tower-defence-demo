#pragma once
#include "cScreen.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class ChooseLevel : public cScreen
{

	public:
		ChooseLevel();
		int Run(sf::RenderWindow& app) override;
};