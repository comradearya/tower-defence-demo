#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <math.h>

struct Bullet
{
	sf::Vector2f dest;
	sf::Vector2f velocity;
	sf::CircleShape shape;
	int radius = 5,
		damage;
	bool needDelete;
	class Enemy* target;

	Bullet(sf::Vector2f dest, sf::Vector2f source, float bulletSpeed, int damage, Enemy* enemy);
	
	void setVelocity(sf::Vector2f source, float bulletSpeed);
	
	bool isGoal();
};
