#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Enemy {
public:
	sf::Sprite * pic = nullptr;
	unsigned path_i = 0;
	sf::Vector2f velocity;
	int hp = 100;
	bool die;
	int prize = 0;
	//float x, y;

	Enemy(sf::Sprite *sprite);

	Enemy(sf::Sprite *sprite, float x, float y);
	
	~Enemy();
	
	void hitted(int damage);
	
	sf::Vector2f getEnemyPos();
};
