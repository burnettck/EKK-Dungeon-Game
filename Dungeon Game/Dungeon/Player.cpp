#include "Player.h"

Player::Player() 
{
	xpos = 0;
	ypos = 0;
}

void Player::setPosition(int x, int y) {
	xpos = x;
	ypos = y;
}

void Player::getPosition(int& x, int& y) {
	x = xpos;
	y = ypos;
}