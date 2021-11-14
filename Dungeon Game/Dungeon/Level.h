#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include <fstream>
#include "Player.h"

using namespace std;


class Level
{
public:
	Level();

	void load(string filen, Player &player);
	void print();

	void playerMove(char input, Player& player);
	void moveAnalysis(char locationTile, char in, Player& player);
	char getLoc(int x, int y);
	void UpdateBoard(int x, int y, char update);
	void getFloor();
	int floor =0;
private:
	vector <string> levelmap;
};

#include "Level.cpp"

#endif