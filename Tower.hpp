#pragma once


struct Tower
{
	int		dmg = 20,
			radius = 3;
	float	reload_time = 120,
			reloading = 0,
			bulletSpeed = 7;
	
	class Enemy*	curentEnemy = nullptr;

	bool canShoot();
};