//
// Created by karne on 9/28/2021.
//

#include "Actor.h"

/*
 * Constructors
 */

//Creates a blank actor with crap stats
Actor::Actor()
{
    this->Name = "Debbie Default";
}

//Creates an actor of a specific level
Actor::Actor(int level, element weakness, std::string Name)
{
    for (level; level > 0; level--)
    {
        levelup();
    }

    makeWeakAgainst(weakness);

    this->Name = Name;
}

//Creates an actor with specific stats
Actor::Actor(int level, int str, int end, int spd, int skl, int sdef, int luk, int maxhp, int maxmp, element weakness, std::string Name)
{
    statistic.level = level;
    statistic.MaxHP = maxhp;
    statistic.CurHP = maxhp;
    statistic.MaxMP = maxmp;
    statistic.CurMP = maxmp;
    statistic.STR = str;
    statistic.END = end;
    statistic.SPD = spd;
    statistic.SKL = skl;
    statistic.SDEF = sdef;
    statistic.LUK = luk;

    makeWeakAgainst(weakness);

    this->Name = Name;

}

/*
 * Mutators
 */

//Increases HP stat by a set amount. Does the same thing as heal() but
//Has no check for the current HP cap.
void Actor::hurt(int amt)
{
    this->statistic.CurHP -= amt;
}

//Increases HP stat by a set amount. Does the same thing as hurt() but
//Has a check for the current HP cap.
void Actor::heal(int amt)
{
    this->statistic.CurHP += amt;
    if (this->statistic.CurHP > this->statistic.MaxHP)
    {
        this->statistic.CurHP = this->statistic.MaxHP;
    }
}

//Decreases MP stat by a set amount. Does the same thing as Manarestore() but
//Has no check for the current MP cap.
void Actor::manadrain(int amt)
{
    this->statistic.CurMP -= amt;
}

//Restores MP stat by a set amount. Does the same thing as Manadrain() but
//Has a check for the current MP cap.
void Actor::manarestore(int amt)
{
    this->statistic.CurMP += amt;
    if (this->statistic.CurMP > this->statistic.MaxMP)
    {
        this->statistic.CurMP = this->statistic.MaxMP;
    }
}


void Actor::levelup()
{
    std::cout<<"Dummy call to level up function"<<std::endl;
}

//This makes the actor weak against a certain element
//Most frequently gonna be called by the Constructor, but maybe it could be
//used by a skill
void Actor::makeWeakAgainst(element elem)
{
    switch (elem)
    {
        case FIRE:
        {
            this->statistic.FIRE = WEAK;
        }
        case WATER:
        {
            this->statistic.WATER = WEAK;
        }
        case AIR:
        {
            this->statistic.AIR = WEAK;
        }
        case EARTH:
        {
            this->statistic.EARTH = WEAK;
        }
        case SPIRIT:
        {
            this->statistic.SPIRIT = WEAK;
        }
        case LIGHT:
        {
            this->statistic.LIGHT = WEAK;
        }
        case DARK:
        {
            this->statistic.DARK = WEAK;
        }
        case PHYSICAL:
        {
            this->statistic.PHYSICAL = WEAK;
        }
    }
}

//1:STR,2:END,3:SPD,4:SKL,5:SDEF,6:LUK
//amt negative for debuff, positive for buff
void Actor::changestat(int amt, int stat)
{
    if (stat == 1)
    {
        this->statistic.STR += amt;
    }
    else if (stat == 2)
    {

        this->statistic.END += amt;
    }
    else if (stat == 3)
    {

        this->statistic.SPD += amt;
    }
    else if (stat == 4)
    {

        this->statistic.SKL += amt;
    }
    else if (stat == 5)
    {

        this->statistic.SDEF += amt;
    }
    else if (stat == 6)
    {

        this->statistic.LUK += amt;
    }
}




/*
 * Accessors
 */

float Actor::getWeaknessMultiplier(element elem)
{
    switch (elem) {
        case FIRE:
            switch (this->statistic.FIRE) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        case WATER:
            switch (this->statistic.WATER) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        case AIR:
            switch (this->statistic.AIR) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        case EARTH:
            switch (this->statistic.EARTH) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        case SPIRIT:
            switch (this->statistic.SPIRIT) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        case LIGHT:
            switch (this->statistic.LIGHT) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        case DARK:
            switch (this->statistic.DARK) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        case PHYSICAL:
            switch (this->statistic.PHYSICAL) {
                case WEAK:
                    return 1.5;
                case STRONG:
                    return 0.25;
                case NORMAL:
                    return 1;
                case DRAIN:
                    return -1;
                case NULLIFY:
                    return 0;
                default:
                    return 1;
            }
        default:
            return 1;
    }
}

/*
 * Stat accessors
 */

//Gets the Strength stat of the actor
int Actor::getstat_str()
{
    return this->statistic.STR;
}

//Gets the endurance stat of the actor
int Actor::getstat_end()
{
    return this->statistic.END;
}

//Gets the speed stat of the actor
int Actor::getstat_spd()
{
    return this->statistic.SPD;
}

//Gets the skill stat of the actor
int Actor::getstat_skl()
{
    return this->statistic.SKL;
}

//gets the skill defense stat of the actor
int Actor::getstat_sdef()
{
    return this->statistic.SDEF;
}

//Gets the luck stat of the actor
int Actor::getstat_luk()
{
    return this->statistic.LUK;
}

//Gets the current HP stat of the actor
int Actor::getHP()
{
    return this->statistic.CurHP;
}

//Gets the current MP stat of the actor
int Actor::getMP()
{
    return this->statistic.CurMP;
}

//Gets the HP cap stat for the actor
int Actor::getMaxHP()
{
    return this->statistic.MaxHP;
}

//Gets the MP cap stat for the actor
int Actor::getMaxMP()
{
    return this->statistic.MaxMP;
}

//Returns a pointer to the actor
Actor* Actor::Me()
{
    return this;
}