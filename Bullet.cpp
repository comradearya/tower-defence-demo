#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f dest, sf::Vector2f source, float bulletSpeed, int damage, Enemy* enemy)
{
	needDelete = false;
	this->dest = dest;
	shape.setRadius(radius);
	shape.setFillColor({ 0, 0, 0 ,255 });
	shape.setPosition(source);
	this->damage = damage;
	target = enemy;
	setVelocity(source, bulletSpeed);
}

void Bullet::setVelocity(sf::Vector2f source, float bulletSpeed)
{
	float	dx, dy, size;
	dx = dest.x - source.x;
	dy = dest.y - source.y;
	size = sqrt(pow(dx, 2) + pow(dy, 2));
	velocity = { dx / size * bulletSpeed, dy / size * bulletSpeed };
}

bool Bullet::isGoal()
{
	return needDelete = abs(shape.getPosition().x - dest.x) < radius * 3 && abs(shape.getPosition().y - dest.y) < radius * 3;
}

