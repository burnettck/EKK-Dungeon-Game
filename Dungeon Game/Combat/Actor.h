//
// Created by karne on 9/28/2021.
//

#ifndef DUNGEON_GAME_ACTOR_H
#define DUNGEON_GAME_ACTOR_H


#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

class Actor {
private:
    //variables
    enum weakness {DRAIN,NULLIFY,STRONG,NORMAL,WEAK};
    struct STAT
    {
        int level = 1;
        int MaxHP = 20;
        int CurHP = 20;
        int MaxMP = 20;
        int CurMP = 20;
        int STR = 5;
        int END = 5;
        int SPD = 5;
        int SKL = 5;
        int SDEF = 5;
        int LUK = 5;

        weakness FIRE = NORMAL;
        weakness WATER = NORMAL;
        weakness AIR = NORMAL;
        weakness EARTH = NORMAL;
        weakness SPIRIT = NORMAL;
        weakness LIGHT = NORMAL;
        weakness DARK = NORMAL;
        weakness PHYSICAL = NORMAL;
    };

    STAT statistic;


public:
    //variables
    std::string Name;

    //constructors
    Actor();
    Actor(int level, element weakness, std::string Name);
    Actor(int level, int str, int end, int spd, int skl, int sdef, int luk, int maxhp, int maxmp, element weakness, std::string Name);


    //mutator functions
    void hurt(int amt);
    void heal(int amt);
    void manadrain(int amt);
    void manarestore(int amt);
    void levelup();
    void makeWeakAgainst(element elem);
    void changestat(int amt, int stat);

    //get functions
    int getstat_str();
    int getstat_end();
    int getstat_spd();
    int getstat_skl();
    int getstat_sdef();
    int getstat_luk();
    int getHP();
    int getMP();
    int getMaxHP();
    int getMaxMP();
    Actor* Me();
    float getWeaknessMultiplier(element elem);

};

#include "Actor.cpp"

#endif //DUNGEON_GAME_ACTOR_H
