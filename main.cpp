#include <vector>
#include <windows.h>
#include <unordered_map>
#include "cScreen.hpp"
#include "screens.hpp"

using namespace std;
using namespace sf;

int main()
{
	vector<cScreen*> screens;
	int screen = 0;
	int money = 200;
	screens.push_back(new MainMenu());
	screens.push_back(new ChooseLevel());
	screens.push_back(new Level("levels/map1.txt", &money));
	screens.push_back(new Level("levels/map2.txt", &money));
	screens.push_back(new Level("levels/map3.txt", &money));
	screens.push_back(new Level("levels/map4.txt", &money));
	screens.push_back(new Level("levels/map5.txt", &money));
	RenderWindow window(VideoMode(800, 640), "Map", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	while (screen >= 0)
	{
		screen = screens[screen]->Run(window);
	}

	return 0;
}
