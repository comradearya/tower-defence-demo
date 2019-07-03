Kyrsach: Bullet.o ChooseLevel.o Enemy.o Level.o Tower.o main.o MainMenu.o
	g++ -g Bullet.o ChooseLevel.o Enemy.o Level.o Tower.o main.o MainMenu.o -o Kyrsach.exe -LC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib -lsfml-graphics -lsfml-system -lsfml-window

Bullet.o: Bullet.cpp
	g++ -g Bullet.cpp -c -IC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include

ChooseLevel.o: ChooseLevel.cpp
	g++ -g ChooseLevel.cpp -c -IC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include

Enemy.o: Enemy.cpp
	g++ -g Enemy.cpp -c -IC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include

Level.o: Level.cpp
	g++ -g Level.cpp -c -IC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include

Tower.o: Tower.cpp
	g++ -g Tower.cpp -c -IC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include

main.o: main.cpp
	g++ -g main.cpp -c -IC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include

MainMenu.o: MainMenu.cpp
	g++ -g MainMenu.cpp -c -IC:/VSCode-win32-x64-1.33.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include`