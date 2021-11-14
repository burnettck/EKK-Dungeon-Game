#include "Level.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

// **********************************************************
// * Name:  Level::Level()                     
// * Description: Default constructor that is just chilling
// * here for now                                        
// * Last Modifed by: Collin Burnett                        
// **********************************************************
Level::Level()
{

}

// **********************************************************
// * Name:  Level::load()                     
// * Description: takes in filename and a reference to player.
// * (player class contains position data gets and sets.) 
// * Opens file, sets "floor" to 1 on level 1 start.                                     
// * Last Modifed by: Collin Burnett                        
// **********************************************************
void Level::load(string filenm, Player &player)
{
	ifstream file;

	file.open(filenm);
									// For collin: Should probably modify so all floor data is obtained from here.
	if (filenm == "level1.txt") {
		Level::floor = 1;
	}
	string line;					// variable that will take in one line at a time of the map file.			
	levelmap.clear();				// clears map file.
	while (getline(file, line))		// loop to get each line from map as line, pushes that line onto the map of the level until EOF.
		levelmap.push_back(line);
	file.close();
	char pos;						//  character that will be used to set player's position on each level.
										
	for (int i = 0; i < levelmap.size(); i++) {			// outer for loop steps through lines
		for (int j = 0; j < levelmap[i].size(); j++) {  // inner loop steps through characters of each line looking for "@"
			pos = levelmap[i][j];						// stores position data after each inner loop
			
			switch (pos) {								// Switch loop to set position of player. Could be expanded to work with items or enemies.
			case '@':									// "@" symbol is found, sets the player's position to that location. 			
				player.setPosition(j, i);
				break;
			}
		}
	}
}

// **********************************************************
// * Name:  Level::print()                     
// * Description: prints current state of the levelmap line 
// * by line.                                    
// * Last Modifed by: Collin Burnett                        
// **********************************************************
void Level::print()
{
	for (int i = 0; i < levelmap.size(); i++) {
		cout << (levelmap[i]) << endl;
	}
	cout << "\n";
}

// **********************************************************
// * Name:  Level::getFloor()                     
// * Description: This ended up being useless, but keeping 
// * it here for now.                              
// * Last Modifed by: Collin Burnett                        
// **********************************************************
void Level::getFloor() {
}

// **********************************************************
// * Name:  Level::playerMove()                     
// * Description: Called by the game move function.
// * Takes in the character input from the user (WASD)
// * as well as player position data.
// * switch looks at corresponding position on the map based
// * on user input. Sends to moveAnalysis to analyze and
// * process what happens based on the character in the 
// * intended space.            
// * Last Modifed by: Collin Burnett                        
// **********************************************************
void Level::playerMove(char input, Player &player)
{
	int x, y;
	player.getPosition(x, y);			// player current position
	char moveLoc;						// the CHARACTER at the intended move space. NOT the space location data.
	char in;							//input to send to further analysis.

	switch (input) {					// Sends intended location data, input character, and current player data to analysis.
	case 'w':
		moveLoc = getLoc(x, y-1);		
		in = 'w';
		moveAnalysis(moveLoc, in, player);	
		break;
	case 'a':
		moveLoc = getLoc(x-1, y);
		in = 'a';
		moveAnalysis(moveLoc, in, player);
		break;
	case 's':
		moveLoc = getLoc(x, y + 1);
		in = 's';
		moveAnalysis(moveLoc, in, player);
		break;
	case 'd':
		moveLoc = getLoc(x + 1, y);
		in = 'd';
		moveAnalysis(moveLoc, in, player);
		break;
	}
}
// **********************************************************
// * Name:  Level::getLoc()                     
// * Description: returns the CHARACTER that is at the input location.
// * Last Modifed by: Collin Burnett                        
// **********************************************************
char Level::getLoc(int x, int y) {
	char location = levelmap[y][x];
	return location;
}

// Here comes the BIG BOY function where combat initiation, item collection, floor to floor traversal, and collision are implemented


// **********************************************************
// * Name:  Level::moveAnalysis()                     
// * Description: Takes in a character that represents the 
// * what is at the intended move space. Takes in the 
// * most recent character input, as well as player location
// * data.
// * Based on what is at the location processes what happens
// * upon movement.  
// * Last Modifed by: Collin Burnett                        
// **********************************************************

void Level::moveAnalysis(char locationTile, char in, Player& player) {
	switch (locationTile) {
	case '#':										// Case of move space being a wall. Doesn't let you move. cout text and pause is just fluff.
		cout << "You gently place your face against the wall. It does not budge." << endl;
		system("PAUSE");
		break;
	case '.':										// Case of move space being accessible floor. Processes movement.
		int x, y;									// variables to take in position data
		player.getPosition(x, y);					// get position data and store into x and y.
		
		// **********************************************************
		//  switch that sets the player's current 
		//  position to the new move space.
		//  Updates  the spaces on the board.
		// **********************************************************
		switch (in) {								
		case 'w':									
			player.setPosition(x, y - 1);
			UpdateBoard(x, y, '.');
			UpdateBoard(x, y - 1, '@');
			break;
		case 'a':
			player.setPosition(x - 1, y);
			UpdateBoard(x, y, '.');
			UpdateBoard(x - 1, y, '@');
			break;
		case 's':
			player.setPosition(x, y + 1);
			UpdateBoard(x, y, '.');
			UpdateBoard(x, y + 1, '@');
			break;
		case 'd':
			player.setPosition(x + 1, y);
			UpdateBoard(x, y, '.');
			UpdateBoard(x + 1, y, '@');
			break;
		}
		break;
	case 'X':										// Case of move space being an ENEMY. Process combat, then movement.					
		cout << "Shia Surprise! It's an Enemy!" << endl;
		cout << "INITIATE COMBAT" << endl;			// Here is where combat would occur.
		system("PAUSE");
													//then if combat is successful....
		player.getPosition(x, y);					// Process movement as before.
		cout << "You emerge victorious..." << endl;
		switch (in) {								// These switches could be a function... will probably adjust later.
		case 'w':
			player.setPosition(x, y - 1);
			UpdateBoard(x, y, '.');
			UpdateBoard(x, y - 1, '@');
			break;
		case 'a':
			player.setPosition(x - 1, y);
			UpdateBoard(x, y, '.');
			UpdateBoard(x - 1, y, '@');
			break;
		case 's':
			player.setPosition(x, y + 1);
			UpdateBoard(x, y, '.');
			UpdateBoard(x, y + 1, '@');
			break;
		case 'd':
			player.setPosition(x + 1, y);
			UpdateBoard(x, y, '.');
			UpdateBoard(x + 1, y, '@');
			break;
		}
		break;
	case 'O':									// Case of move space being an CHEST. Process object acquisition, then movement.	
		cout << "You find a chest!" << endl; 	
		cout << "Commence Lootage." << endl;    // Here is where object interaction would occur.
		system("PAUSE");
		player.getPosition(x, y);				// process movement as before. could DEFINITELY be a function. will fix. will help clarity.
		switch (in) {
		case 'w':
			player.setPosition(x, y - 1);
			UpdateBoard(x, y, '.');
			UpdateBoard(x, y - 1, '@');
			break;
		case 'a':
			player.setPosition(x - 1, y);
			UpdateBoard(x, y, '.');
			UpdateBoard(x - 1, y, '@');
			break;
		case 's':
			player.setPosition(x, y + 1);
			UpdateBoard(x, y, '.');
			UpdateBoard(x, y + 1, '@');
			break;
		case 'd':
			player.setPosition(x + 1, y);
			UpdateBoard(x, y, '.');
			UpdateBoard(x + 1, y, '@');
			break;
		}
		break;
	case 'H':									// Case of move space being a LADDER. Asks if user would like to proceed.
		cout << "You find a ladder!" << endl;
		cout << "Would you like to advance? y/n" << endl;
		char choice;
		choice = _getch();
		switch (choice) {
		case 'y':								//  based on which floor you're currently on, loads a new floor. Can be infinitely scaled. Only allows for forward progression at the moment.
			cout << "You climb the ladder." << endl;  
				switch (Level::floor) {
				case 1:
					load("level2.txt", player);
					Level::floor = 2;
					cout << string(100, '\n');
					cout << "You have entered the den of sin." << endl;
					system("PAUSE");
					break;
				case 2:
					load("level3.txt", player);
					Level::floor = 3;
					cout << string(100, '\n');
					cout << "You have entered the pit of...death? \n Destruction!! \n DOOOOOM." << endl;
					system("PAUSE");
					break;
				case 3:
					load("boss.txt", player);
					Level::floor = 4;
					cout << string(100, '\n');
					cout << "You have entered Ronald McDonald's playplace." << endl;
					system("PAUSE");
					break;
				case 4:
					load("victoryroom.txt", player);
					cout << string(100, '\n');
					cout << "Cue Victory Fanfare!" << endl;
					system("PAUSE");
						break;
				}
			break;
		case 'n':										// case where user doesn't wanna go.
			cout << "You remain where you are.";
			break;
		default:										// default case so game doesnt blow up if user fat fingers.
			cout << "You remain where you are.";

		}
			break;
	}
}




// **********************************************************
// * Name:  Level::UpdateBoard()                     
// * Description: Updates what charcter resides in a 
// * certain spot in the map.  
// * Last Modifed by: Collin Burnett                        
// **********************************************************
void Level::UpdateBoard(int x, int y, char update) {
	levelmap[y][x] = update;
}