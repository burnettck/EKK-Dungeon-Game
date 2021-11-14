#include "Game.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <conio.h>

// **********************************************************
// * Name:  Game::Game(string levelmap)                      
// * Description: takes in the array of strings from levelmap
// * and calls load.                                           
// * Last Modifed by: Collin Burnett                        
// **********************************************************
Game::Game(string levelmap)
{
	level.load(levelmap, player);
	//level.print();
}

// **********************************************************
// * Name:  Game::play()                     
// * Description: The game loop. Prints the state of the game
// * after the most recent move, and calls the move function.
// * Cout string helps with formatting in the current build.                                           
// * Last Modifed by: Collin Burnett                        
// **********************************************************
void Game::play() 
{
	bool done = false;
	while (done != true) {
		cout << string(100, '\n');
		level.print();
		move();
	}
}

// **********************************************************
// * Name:  Game::move()                     
// * Description: move function. Takes input from user. Calls
// * playerMove with the current player state and input char                                         
// * Last Modifed by: Collin Burnett                        
// **********************************************************
void Game::move() {
	char input=0;
	input = _getch();
	level.playerMove(input, player);
}