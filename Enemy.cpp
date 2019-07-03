#include "Enemy.hpp"
Enemy::Enemy(sf::Sprite *sprite) {
		pic = sprite;
		velocity.x = 0;
		velocity.y = 0;
	}

Enemy::Enemy(sf::Sprite *sprite, float x, float y) {
		pic = sprite;
		pic -> setTextureRect(sf::IntRect(0, 57, 21, 29));
		this->velocity.x = x;
		this->velocity.y = y;
	}
Enemy::~Enemy()
	{
		delete this->pic;
		delete this;
	}

	void Enemy::hitted(int damage)
	{
		this->hp -= damage;
		if (this->hp <= 0)
		{
			this->die = true;
			this->prize = 30;
		}

	}

	sf::Vector2f Enemy::getEnemyPos()
	{
		return pic->getPosition();
	}

