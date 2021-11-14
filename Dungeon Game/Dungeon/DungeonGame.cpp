#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>

#include "Game.h"
#include "Level.h"
#include "../Combat/Combat.cpp"
#include "../Combat/Actor.h"
#include "../Combat/Skill.h"


using namespace std;

int Game_main() {
    cout << string(100, '\n');
    cout << "Hey...you...you're finally awake....." << endl;
    system("PAUSE");
    cout << string(100, '\n');
    cout << "Well..that's what you wish someone said..." << endl;
    system("PAUSE");
    cout << string(100, '\n');
    cout << "You find yourself alone in one of the darkest dungeons you have ever seen... \n ...You've never seen a dungeon, so it checks out." << endl;
    system("PAUSE");
    cout << string(100, '\n');
    cout << "You've gotta get out of here...    " << endl;
    system("PAUSE");
    Game game("level1.txt");

    game.play();

    return 0;
}

