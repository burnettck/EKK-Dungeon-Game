#include <iostream>
#include <iomanip>
#include "../Dungeon/DungeonGame.cpp"
using namespace std;

void Menu() {

    char choose;

    do { //do while loop to keep looping in case the player looks at credits
        cout << "Dungeon Game" << endl; //idk what to put for the name
        cout << "Choose an option below" << endl; //prompts player to choose
        cout << "1 Start a New Game" << endl; //play game choice
        cout << "2 Credits" << endl; //show credits choice
        cout << "3 Quit Game" << endl; //quit game choice
        cin >> setw(0) >> choose; //player input
        cout << endl; //line for organization

        if (choose != '1' && choose != '2' && choose != '3') {
            do { //do while loop to loop in case player can't read
                cout << "Invalid option - Choose an option below" << endl; //if the player can't read
                cout << "1 Start a New Game" << endl; //play game choice
                cout << "2 Credits" << endl; //show credits choice
                cout << "3 Quit Game" << endl; //quit game choice
                cin >> choose; //player input
                cout << endl; //line for organization
            } while (choose != '1' && choose != '2' && choose != '3'); //while they figure out how to read
        } //if

       /* if (choose > 0) {
            //do { //do while loop to loop in case player can't read
                cout << "Invalid option - Choose an option below" << endl; //if the player can't read
                cout << "1 Start a New Game" << endl; //play game choice
                cout << "2 Credits" << endl; //show credits choice
                cout << "3 Quit Game" << endl; //quit game choice
                cin >> choose; //player input
                cout << endl; //line for organization
                break;
            //} while (choose > 0); //while they figure out how to read
        }*/

        switch (choose) { //switch case for whatever the player put
            case '1': //if player wants to play the game
                Game_main();
                break; //breaks case
            case '2': //if player wants to see credits
                cout << "Combat Designer - Kenneth Terwilliger" << endl; //Kenneth
                cout << "Dungeon Designer - Collin Burnett" << endl; //Collin
                cout << "UI Designer - Ersoy Demir" << endl; //Ersoy
                cout << "© 2021 EKK Interactive\n" << endl; //copyright cause our game
                break; //breaks case
            case '3': //if player wants to quit
                cout << "Thanks for playing!" << endl; //bye message
                break; //breaks case
        } //switch
    } while (choose != '3'); //while to end loop
} //void

int main() {
    Menu();
    return 0;
}