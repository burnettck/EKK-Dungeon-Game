#ifndef PLAYER_H
#define PLAYER_H
class Player
{
public:
	Player();

	void setPosition(int x, int y);

	void getPosition(int& x, int& y);

private:
	int xpos;
	int ypos;

};

#include "Player.cpp"

#endif