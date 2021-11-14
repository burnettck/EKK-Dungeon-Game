#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Level.h"
#include <string>

using namespace std;

class Game
{
public:

	Game(string levelmap);

	void play();
	void move();

private: 
	Player player;
	Level level;
};

#include "Game.cpp"

#endif