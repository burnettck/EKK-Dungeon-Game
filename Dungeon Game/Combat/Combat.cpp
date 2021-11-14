
/*
OF NOTE:
The equation for attack damage is this:
DMG = (5 x sqrt(ST/EN x ATK) x MOD X RND) / WKN
 Some skills may attack more than once.
 Minimum damage is 5 - attacks that land should never do no damage.

DMG = Damage
ST = Character's Strength stat
EN = Enemy's Endurance stat
ATK = Atk value of equipped weapon OR Pwr value of used skill
MOD = Modifier based on the difference between character level and enemy level
RND = Randomness factor (roughly between 0.95 and 1.05)
WKN = Weakness multiplier. -1 for Drain, 0 for Null, 0.5 for strong, 1 for normal, 1.5 for weak
 */

enum element {FIRE,WATER,AIR,EARTH,SPIRIT,LIGHT,DARK,PHYSICAL};

#include "Actor.h"
#include "Skill.h"


using namespace std;


//######################## Prototype Functions #########################//
//Handlers
void combat_initiate();
int roll_dice(int dice_sides, int dice_number);
int damage(Actor *attacker, Actor *defender);

//Actions
bool attack(Actor *attacker, vector<Actor> *defenders, element elem);

//Main Loop
bool main_combat_loop(vector<Actor> *Friend, vector<Actor> *Foe);

/*
 * **************************************************************************
 * Handler functions. Handles background functions for the roller.          *
 * Stuff like Math, loading/unloading statistics, etc.                      *
 * **************************************************************************
 */

void combat_initiate()
{
    vector<Actor> Friendlies;
    vector<Actor> Enemies;
    vector<Actor> * Friendlies_ptr = &Friendlies;
    vector<Actor> * Enemies_ptr = &Enemies;
    bool victory;

    srand(time(NULL));

    //in the future, should accept inputs that will determine what and how many Actors are created.
    Actor Hero(1,20,20,10,10,15,5,80,10,FIRE,"Hero");
    Actor Villain1(1,20,10,15,10,15,5,40,10,PHYSICAL,"Dodgy Creature");
    Actor Villain2(1,20,10,5,10,15,5,40,10,PHYSICAL,"Slow Creature");

    Friendlies.push_back(Hero);
    Enemies.push_back(Villain1);
    Enemies.push_back(Villain2);



    victory = main_combat_loop(Friendlies_ptr,Enemies_ptr);

    if (victory)
    {
        cout<<"Hero Won!"<<endl;
    }
    else
    {
        cout<<"Hero Lost!"<<endl;
    }
}


int roll_dice(int dice_sides, int dice_number)
{
    int total = 0;
    int roll = 0;

    //This loop is what actually rolls the dice
    for (int i = 0; i < dice_number; i++)
    {
        roll = rand() % dice_sides + 1;
        total = total + roll;
    }

    return total;
}

int damage(Actor attacker, Actor defender, element elem)
{
    int DMG;
    float MOD;
    float RND;
    float WKN = 1;
    RND = float((fmod(double(roll_dice(100,1)),0.1)) + 0.95);
    if (defender.isWeakAgainst(elem))
    {
        WKN = 1.5;
    }

    DMG = int(5 + (5 * sqrt(attacker.getstat_str()/defender.getstat_end() * 1) * 1 * RND) * WKN);

    cout<<"Dealt "<<DMG<<" Damage!"<<endl;

    return DMG;

}

/*
 * **************************************************************
 * Action functions. Handles actions                            *
 * **************************************************************
 */

bool attack(Actor *attacker, Actor *defender, element elem)
{
    bool is_crit = false; //Is it a crit?

    //This is out here so I can see the values.
    int to_hit = roll_dice(attacker->getstat_spd()+attacker->getstat_luk(),1);
    int dodge = roll_dice(defender->getstat_spd(),1);


    if (to_hit >= dodge)
    {
        //Critical Roll
        if (roll_dice(100,1) + attacker->getstat_luk() >= 100)
            is_crit = true;
        else
            is_crit = false;


        cout<<defender->Name<<" is hit!"<<endl;
        if (is_crit)
        {
            int dam = damage(*attacker, *defender, elem);
            cout<<"CRITICAL HIT!"<<endl;
            defender->hurt( dam * 2);
            cout<<dam<<" damage!"<<endl;
        }
        else if (!is_crit)
        {
            int dam = damage(*attacker, *defender, elem);
            defender->hurt(dam);
            cout<<dam<<" damage!"<<endl;
        }

    }
    else
    {
        cout<<attacker->Name<<" misses!"<<endl;
    }

    return true;
}

bool basic_attack(Actor *attacker, vector<Actor> *defenders, element elem)
{
    int player_input;

    if (defenders->size() > 1)
    {
        cout<<"Which enemy would you like to attack?"<<endl<<endl;
        //display a dynamic list of enemies
        for (int i = 0; i < defenders->size(); i++)
        {
            cout<<i+1<<".\t"<<(defenders->begin() + i)->Name<<endl;
        }
        cout<<endl;
        cin>>player_input;
        player_input -= 1;
        try
        {
            cout<<"\n\n\n"<<attacker->Name<<" attacks "<<(defenders->begin() + player_input)->Name<<"!"<<endl;
            attack(attacker,(defenders->begin() + player_input)->Me(), PHYSICAL);
            return true;
        }
        catch (...)
        {
            while (player_input >= defenders->size() || player_input <= 0)
            {
                cout<<"There's no enemy like that!"<<endl;
                cout<<endl;
                cin>>player_input;
            }
            player_input -= 1;

            cout<<"\n\n\n"<<attacker->Name<<" attacks "<<(defenders->begin() + player_input)->Name<<"!"<<endl;
            attack(attacker,(defenders->begin() + player_input)->Me(), PHYSICAL);
            return true;
        }
    }
    else
    {
        player_input = 0;
        cout<<"\n\n\n"<<attacker->Name<<" attacks "<<(defenders->begin() + player_input)->Name<<"!"<<endl;
        attack(attacker,(defenders->begin() + player_input)->Me(), PHYSICAL);
        return true;
    }
}

/*
 * **************************************************************
 * Main Combat Loop stuff. Handles the main combat loop.        *
 * **************************************************************
 */

bool main_combat_loop(vector<Actor> *Friend, vector<Actor> *Foe)
{
    int round = 1;
    while (!Foe->empty() && !Friend->empty())
    {
        Actor * Turn;
        for (int i = 0; i < Friend->size(); i++)
        {
            Turn = (Friend->begin() + i)->Me();
            basic_attack(Turn,Foe,PHYSICAL);
            int temp = 0;
            for (Actor a : *Foe)
            {
                if (a.getHP() <= 0)
                {
                    cout<<a.Name<<" perishes..."<<endl;
                    Foe->erase(Foe->begin() + temp);
                }
                temp++;
            }
        }


        for (int i = 0; i < Foe->size(); i++)
        {
            Turn = (Foe->begin() + i)->Me();
            basic_attack(Turn,Friend,PHYSICAL);
            int temp = 0;
            for (Actor a : *Friend)
            {
                if (a.getHP() <= 0)
                {
                    cout<<a.Name<<" perishes..."<<endl;
                    Friend->erase(Friend->begin() + temp);
                }
                temp++;
            }
        }
        round++;
    }

    if (Foe->empty())
    {
        cout<<"All Foes Defeated"<<endl;
        cout<<"Combat took "<<round<<" round(s)!"<<endl;
        return true;
    }
    else if (Friend->empty())
    {
        cout<<"All Friends Defeated"<<endl;
        cout<<"Combat took "<<round<<" round(s)!"<<endl;
        return false;
    }

    //unreachable, just to make CLion stop complaining.
    return false;
}
