/*
    This file is part of Dreaming Warrior.

    Dreaming Warrior is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dreaming Warrior is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Dreaming Warrior.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef INCLUDE_H
#define INCLUDE_H

#define KROFNA_JE_CAR true

#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

#define MAX_ITEMS 30
#define MAX_SPELLS 5 //PH? nepotrebno

enum ItemType
{
    ITEM_QUEST,

    ITEM_HEALTH_POTION,
    ITEM_POWER_POTION,

    ITEM_HEAD,
    ITEM_CHEST,
    ITEM_HANDS,
    ITEM_LEGS,
    ITEM_FOOT,
    ITEM_WEAPON,
    ITEM_SHIELD,
    ITEM_FOOD,
    ITEM_MANA_FOOD
};

enum Attribute
{
    NO_ATTRIBUTE,
    HEALTH,
    POWER,
    ATTACK_POWER, // Melee or Spell Power
    DEFENSE_POWER,
    INT_OR_STR
};

inline int urand(int MIN, int MAX)
{
    return (rand()%(MAX-MIN+1) + MIN);
}

inline string IntToString(int Integer)
{
    stringstream convert;
    convert << Integer;
    return convert.str();
}

enum ObjectType
{
    NO_OBJECT,
    SOLID_OBJECT,
    ENEMY,
    VENDOR,
    QUEST
};

enum Orientation
{
    NORTH,
    SOUTH,
    WEST,
    EAST
};

enum GameMode
{
    NEW_GAME,
    LOAD_GAME
};

enum QuestType
{
    KILL,
    ITEM
};

enum SpellType
{
    SPELL_ATTACK,
    SPELL_HEAL
};

enum Class
{
    CLASS_WARRIOR,
    CLASS_MAGE
};

#endif