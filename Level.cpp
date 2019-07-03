#include "Level.hpp"
#include <unordered_map>

using namespace std;
using namespace sf;

void Level::readmap(string path) {

	unordered_map<string, string> a;

	sand.loadFromFile("images/sand.jpg");
	pave.loadFromFile("images/pavement.jpg");
	spawn.loadFromFile("images/spawn.jpg");
	house.loadFromFile("images/house.jpg");
	green.loadFromFile("images/green.jpg");

	ssand.setTexture(sand);
	spave.setTexture(pave);
	sspawn.setTexture(spawn);
	shouse.setTexture(house);
	sgreen.setTexture(green);

	ifstream mapfile(path, ios::in);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			mapfile >> Map[i][j].type;
			if (Map[i][j].type == 'f') {
				start.first = i;
				start.second = j;
				Map[i][j].sprite = &shouse;
			}
			if (Map[i][j].type == 's') {
				finish.first = i;
				finish.second = j;
				Map[i][j].sprite = &sspawn;
			}
			if (Map[i][j].type == 'o') Map[i][j].sprite = &ssand;
			if (Map[i][j].type == 'M') Map[i][j].sprite = &spave;
			if (Map[i][j].type == 'i') Map[i][j].sprite = &sgreen;
		}
	}
	mapfile.close();
}

Level::Level(string valuePath, int *money)
{
	playerMoney = money;
	readmap(valuePath);
	pathFinder();
}

bool Level::pathFinder()
{
	queue<pair<int, int>> needcheck;
	bool checked[20][20] = { { false } };
	bool find = false;

	pair<int, int> move[20][20], current;
	short	k[] = { 0, -1, 1, 0 },
			m[] = { -1, 0, 0, 1 };

	bool f[] = { start.second != 0, start.first != 0, start.first != 19, start.second != 19 };

	for (int i = 0; i < 4; ++i)
	{
		if (f[i] && Map[start.first + k[i]][start.second + m[i]].type == 'M')
		{
			checked[start.first + k[i]][start.second + m[i]] = true;
			needcheck.emplace(start.first + k[i], start.second + m[i]);
			move[start.first + k[i]][start.second + m[i]].first = start.first;
			move[start.first + k[i]][start.second + m[i]].second = start.second;
		}
	}

	while (!find && !needcheck.empty())
	{
		current = needcheck.front();
		needcheck.pop();
		for (int i = 0; i < 4; i++) {
			if (Map[current.first + k[i]][current.second + m[i]].type == 's')
			{
				find = true;
				move[current.first + k[i]][current.second + m[i]].first = current.first;
				move[current.first + k[i]][current.second + m[i]].second = current.second;
			}


			if (Map[current.first + k[i]][current.second + m[i]].type == 'M' && !checked[current.first + k[i]][current.second + m[i]])
			{
				needcheck.emplace(current.first + k[i], current.second + m[i]);
				checked[current.first + k[i]][current.second + m[i]] = true;
				move[current.first + k[i]][current.second + m[i]].first = current.first;
				move[current.first + k[i]][current.second + m[i]].second = current.second;

			}
		}
	}
	if (find)
	{
		path.clear();
		path.push_back(finish);
		path.push_back(move[finish.first][finish.second]);
		while (!(current.first == start.first && current.second == start.second))
		{
			path.push_back(move[current.first][current.second]);
			current = move[current.first][current.second];
		}

		return true;
	}

	cerr << "Path not found\n";
	return false;
}

void Level::setTower(Tower *tower, int x, int y)
{
	Map[x][y].tower = tower;
}

Enemy* Level::isAnyEnemyInTowerZone(const int x, const int y, const int zoneSize)
{
	for (auto enemy : enemies)
	{
		float ex = enemy->pic->getPosition().x + 16;
		float ey = enemy->pic->getPosition().y + 16;
		if (ex >= x && ex <= x + zoneSize && ey >= y && ey <= y + zoneSize)
			return enemy;
	}
	return nullptr;
}

Enemy* Level::isEnemyInTowerZone(const int x, const int y, const int zoneSize, Enemy* enemy)
{
	float ex, ey;
	try
	{
		if (!enemy->die)
		{
			ex = enemy->pic->getPosition().x + 16;
			ey = enemy->pic->getPosition().y + 16;
			if (ex >= x && ex <= x + zoneSize && ey >= y && ey <= y + zoneSize)
				return enemy;
		}
	}
	catch (...) {}
	return nullptr;
}


int Level::Run(sf::RenderWindow &window) {


	Texture	tex, towerTexture;
	Sprite	eSprite, towerSprite, shopTower;
	Sprite *selected = nullptr;

	RectangleShape bg({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) });
	bg.setFillColor({ 100,60,60,255 });

	Font font;
	if (!font.loadFromFile("verdanab.ttf"))
	{
		std::cerr << "Error load font verdanab.ttf";
		exit(1);
	}
	Text money;
	money.setFont(font);
	money.setCharacterSize(16);
	money.setPosition({ 645.0, 20 });
	money.setFillColor(sf::Color(255, 255, 255, 255));

	if (!tex.loadFromFile("images/enemy.png"))
		cerr << "Cannot load texture from images/enemy.png!\n";
	else
		eSprite.setTexture(tex);

	if (!towerTexture.loadFromFile("images/tower.png"))
		cerr << "Cannot load texture from images/tower.png\n";
	else
	{
		towerSprite.setTexture(towerTexture);
		shopTower.setTexture(towerTexture);
	}

	shopTower.setPosition(700, 70);

	//setTower(new Tower(), 5, 10);
	//setTower(new Tower(), 10, 5);

	float	tick = 0,
		resp_timer = 4.0,
		delay = 0.1,
		speed = 1.0,
		animtime;

	int towerLevel1Cost = 100;

	Clock clock;

	while (window.isOpen())
	{
		window.clear();
		window.draw(bg);
		money.setString("Money: " + std::to_string(*this->playerMoney));
		window.draw(money);



		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		tick += time;
		resp_timer += time;

		animtime += time * 3;
		if (animtime > 3.5) animtime = 0;

		if (resp_timer > 5)
		{
			enemies.push_front(new Enemy(new Sprite(tex), (path[1].first - path[0].first)*speed,
				(path[1].second - path[0].second)*speed));
			enemies.front()->pic->setPosition(path[0].first * 32, path[0].second * 32);
			resp_timer = 0;
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return -1;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					return 0;
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					auto mbp = event.mouseButton;
					if (selected == nullptr)
					{
						if (mbp.x >= shopTower.getPosition().x && mbp.x <= shopTower.getPosition().x + 32
							&& mbp.y >= shopTower.getPosition().y && mbp.y <= shopTower.getPosition().y + 32
							&& *playerMoney >= towerLevel1Cost)
						{
							selected = &shopTower;
						}
					}
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (selected != nullptr)
					{
						auto mbr = event.mouseButton;
						if (Map[mbr.x / 32][mbr.y / 32].type == 'i')
						{
							Map[mbr.x / 32][mbr.y / 32].tower = new Tower();
							cout << "Tower was placed on the map \n";
							*playerMoney -= towerLevel1Cost;
						}
						selected->setPosition(700, 70);
						selected = nullptr;
					}
				}
			}
			if (event.type == Event::MouseMoved)
			{
				if (selected != nullptr)
				{
					auto mm = event.mouseMove;
					selected->setPosition(static_cast<float>(mm.x), static_cast<float>(mm.y));
				}
			}
		}
		int x = -10, y = -10, size = 1;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				Map[i][j].sprite->setPosition(32 * i, 32 * j);
				window.draw(*Map[i][j].sprite);
				if (Map[i][j].tower != nullptr)
				{
					towerSprite.setPosition(32 * i + 6, 32 * j - 8);
					window.draw(towerSprite);

					if (Map[i][j].tower->reloading > 0)
						--Map[i][j].tower->reloading;

					if (Map[i][j].tower->curentEnemy == nullptr)
						Map[i][j].tower->curentEnemy =
						isAnyEnemyInTowerZone(
							i * 32 - Map[i][j].tower->radius * 32,
							j * 32 - Map[i][j].tower->radius * 32,
							Map[i][j].tower->radius * 2 * 32 + 32);
					else
						Map[i][j].tower->curentEnemy =
						isEnemyInTowerZone(
							i * 32 - Map[i][j].tower->radius * 32,
							j * 32 - Map[i][j].tower->radius * 32,
							Map[i][j].tower->radius * 2 * 32 + 32,
							Map[i][j].tower->curentEnemy);

					if (Map[i][j].tower->curentEnemy != nullptr)
						if (Map[i][j].tower->canShoot())
						{
							bullets.push_back(new Bullet(
								{ Map[i][j].tower->curentEnemy->getEnemyPos().x + Map[i][j].tower->curentEnemy->velocity.x * 15,
								Map[i][j].tower->curentEnemy->getEnemyPos().y + Map[i][j].tower->curentEnemy->velocity.y * 15 },
								{ static_cast<float> (i * 32), static_cast<float> (j * 32) },
								Map[i][j].tower->bulletSpeed,
								Map[i][j].tower->dmg,
								Map[i][j].tower->curentEnemy));
						}
				}
			}
		}

		for (auto enemy : enemies)
		{
			enemy->pic->move(enemy->velocity);
			if (enemy->velocity.x == 1)
				enemy -> pic -> setTextureRect(IntRect(0 + 21*int(animtime), 57, 21, 29));
			if (enemy->velocity.x == -1)
				enemy -> pic -> setTextureRect(IntRect(0 + 21*int(animtime), 29, 21, 29));
			if (enemy->velocity.y == 1)
				enemy -> pic -> setTextureRect(IntRect(0 + 21*int(animtime), 0, 21, 29));
			if (enemy->velocity.y == -1)
				enemy -> pic -> setTextureRect(IntRect(0 + 21*int(animtime), 86, 21, 29));

			window.draw(*enemy->pic);
			if (!(enemy->pic->getPosition().x + 32 >= path[enemy->path_i].first * 32
				&& enemy->pic->getPosition().x <= path[enemy->path_i].first * 32 + 32
				&& enemy->pic->getPosition().y <= path[enemy->path_i].second * 32 + 32
				&& enemy->pic->getPosition().y + 32 >= path[enemy->path_i].second * 32))
			{
				++enemy->path_i;
				if (enemy->path_i + 1 == path.size() - 1)
				{
					enemy->die = true;
					cout << "Game Over!\n";
					while (true)
					{
						window.clear();
						money.setCharacterSize(50);

						money.setPosition({ 230, 200 });
						money.setFillColor(sf::Color(255, 0, 0, 255));
						money.setString("Game over!");
						bg.setFillColor({ 0, 0, 0, 180 });
						window.draw(bg);
						window.draw(money);
						window.display();
						while (window.pollEvent(event))
						{
							if (event.type == Event::Closed)
							{
								window.close();
								return 0;
							}
							if (event.type == Event::KeyPressed)
							{
								if (event.key.code == Keyboard::Escape)
									return 0;
							}
						}
					}

				}
				enemy->velocity.x = (path[enemy->path_i + 1].first - path[enemy->path_i + 0].first)*speed;
				enemy->velocity.y = (path[enemy->path_i + 1].second - path[enemy->path_i + 0].second)*speed;
			}
		}
		for (auto bullet : bullets)
		{
			bullet->shape.move(bullet->velocity);
			window.draw(bullet->shape);
			if (bullet->isGoal())
				bullet->target->hitted(bullet->damage);
		}
		for (auto enemy : enemies)
		{
			*playerMoney += enemy->prize;
		}
		enemies.erase(remove_if(begin(enemies), end(enemies),
			[](const Enemy* enemy)
		{
			return enemy->die;
		}),
			end(enemies));

		bullets.erase(remove_if(begin(bullets), end(bullets),
			[](const Bullet* bullet)
		{
			return bullet->needDelete;
		}),
			end(bullets));

		window.draw(shopTower);
		window.display();
	}
	return true;
}
