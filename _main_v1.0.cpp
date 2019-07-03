//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <SFML/Graphics.hpp>
#include <windows.h>
//#include <hash_map>
#include <unordered_map>

using namespace std;
using namespace sf;

class enemy {
public:
	Texture tpic;
	Sprite pic;
	pair<unsigned, unsigned> posofenemy;
	unsigned path_i = 0;
	//float x, y;
	enemy(string enemypath) {
		tpic.loadFromFile(enemypath);
		pic.setTexture(tpic);
	}
};

class level {
	Texture pave, sand, spawn, house, green;
	Sprite spave, ssand, sspawn, shouse, sgreen;
public:

	struct field {
		char type;
		class Element;
		Sprite *sprite;
	};

	int k;
	field Map[20][20];
	Vector2f path2f;
	vector<Vector2f> pathf;
	vector<pair<unsigned, unsigned>> path;
	pair<unsigned, unsigned>	start,
		finish;

	void readmap(string path) {

		unordered_map<string, string> a;
		a["dsf"] = "dshigjft4335";
		try {
			cout << a.at("aaa") << '\n';
		}
		catch (...)
		{
			cout << "Object not found\n";
		}

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
				if (Map[i][j].type == 'i') Map[i][j].sprite= &sgreen;
			}
		}
		mapfile.close();
	}

	level(string valuePath) {
		readmap(valuePath);
	}

	bool pathFinder()
	{
		queue<pair<unsigned, unsigned>>		_queue;
		bool								checked[20][20] = { { false } },
			find = false;
		pair<unsigned, unsigned>			move[20][20],
			current;

		if (start.second != 0 && Map[start.first][start.second - 1].type == 'M')
		{
			checked[start.first][start.second - 1] = true;
			_queue.emplace(start.first, start.second - 1);
			move[start.first][start.second - 1].first = start.first;
			move[start.first][start.second - 1].second = start.second;
		}
		if (start.first != 0 && Map[start.first - 1][start.second].type == 'M')
		{
			checked[start.first - 1][start.second] = true;
			_queue.emplace(start.first - 1, start.second);
			move[start.first - 1][start.second].first = start.first;
			move[start.first - 1][start.second].second = start.second;
		}
		if (start.first != 19 && Map[start.first + 1][start.second].type == 'M')
		{
			checked[start.first + 1][start.second] = true;
			_queue.emplace(start.first + 1, start.second);
			move[start.first + 1][start.second].first = start.first;
			move[start.first + 1][start.second].second = start.second;
		}
		if (start.second != 19 && Map[start.first][start.second + 1].type == 'M')
		{
			checked[start.first][start.second + 1] = true;
			_queue.emplace(start.first, start.second + 1);
			move[start.first][start.second + 1].first = start.first;
			move[start.first][start.second + 1].second = start.second;
		}

		short	k[] = { 0, -1, 1, 0 },
			m[] = { -1, 0, 0, 1 };
		while (!find && !_queue.empty())
		{
			current = _queue.front();
			_queue.pop();
			for (int i = 0; i < 4; i++) {
				if (Map[current.first + k[i]][current.second + m[i]].type == 's')
				{
					find = true;
					move[current.first + k[i]][current.second + m[i]].first = current.first;
					move[current.first + k[i]][current.second + m[i]].second = current.second;
				}


				if (Map[current.first + k[i]][current.second + m[i]].type == 'M' && !checked[current.first + k[i]][current.second + m[i]])
				{
					_queue.emplace(current.first + k[i], current.second + m[i]);
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
			//pathf.reserve(path.size());
			// for (int i = 0; i < path.size(); i++) {
			// 	pathf[i].x = path[i].first;
			// 	pathf[i].y = path[i].second;
			// 	cout << pathf[i].x << "          " << pathf[i].y << endl;
			// }
			/*	for (int i = 0; i <  path.size(); i++)
			{
			cout << path[i].first << ' ' << path[i].second << '\n';
			}*/
			//cout << endl << path.size() << endl << endl;
			//int ps = (int)path.size();
			return true;
		}

		cerr << "Path not found\n";
		return false;
	}

	Sprite s;
	Texture tex;
	bool printmap() {

		// HWND hConsole = GetConsoleWindow();
		// ShowWindow(hConsole, SW_HIDE);

		RenderWindow window(VideoMode(640, 640), "Map", Style::Titlebar|Style::Close);
		tex.loadFromFile("images/poroh.jpg");
		s.setTexture(tex);
		unsigned path_i = 0;
		
		float	tick = 0,
				resp_timer = 0,
				delay = 0.2;

		Clock clock;
		s.setPosition(32 * path[path_i].first + 2, 32 * path[path_i].second+ 2);
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			tick += time;
			resp_timer += 0;

			if (resp_timer > 5)
			{
				
				resp_timer = 0;
			}

			if (tick > delay)
			{
				++path_i;
				if (path_i == path.size()) path_i = 0;
				s.setPosition(32 * path[path_i].first + 2, 32 * path[path_i].second + 2);
				tick = 0;
			}

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
					return false;
				}
			}
			window.clear();
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					Map[i][j].sprite -> setPosition(32 * i, 32 * j);
					window.draw(*Map[i][j].sprite);
				}
			}

			window.draw(s);
			window.display();
		}
		return true;
	}
};

int main() {
	level newmap("map.txt");
	newmap.pathFinder();
	newmap.printmap();
	
	//getchar();
	return 0;
}
