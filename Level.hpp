#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "cScreen.hpp"
#include "tower.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <list>

using namespace std;
using namespace sf;

class Level : public cScreen {

	Texture pave, sand, spawn, house, green;
	Sprite spave, ssand, sspawn, shouse, sgreen;

	list<class Enemy*> enemies;
	list<class Bullet*> bullets;

	int* playerMoney;

	Enemy* isAnyEnemyInTowerZone(int x, int y, int zoneSize);

	Enemy* isEnemyInTowerZone(int x, int y, int zoneSize, Enemy* enemy);

	void setTower(Tower *tower, int x, int y);

public:
	struct field {
		char type;
		Tower *tower=nullptr;
		Sprite *sprite;
	};

	int k;
	field	Map[20][20];
	vector<pair<int, int>>	path;

	pair<int, int>			start,
		finish;

	int Run(sf::RenderWindow& app) override;

	Level(string valuePath, int *money);

	void readmap(string path);

	bool pathFinder();
};





