/*
    This file is part of Game Project.

    Game Project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Game Project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Game Project.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef INCLUDE_H
#define INCLUDE_H

#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::endl;

#define BACKPACK_SIZE 20 //PH
#define MAX_SPELLS 5 //PH?

enum ItemType
{
    ITEM_QUEST,

    ITEM_HEALTH_POTION,
    ITEM_POWER_POTION,

    ITEM_HEAD,
    ITEM_SHOULDERS,
    ITEM_CHEST,
    ITEM_HANDS,
    ITEM_LEGS,
    ITEM_FOOT,

    ITEM_MAINHAND,
    ITEM_OFFHAND
};

enum Attribute
{
    NO_ATTRIBUTE,
    HEALTH,
    POWER,
    ATTACK_POWER, // Melee or Spell Power
    ARMOR,
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
/*
enum MainMenuResult
{
    DEFAULT_NEW,
    DEFAULT_LOAD,
    CUSTOM_NEW,
    CUSTOM_LOAD,
    EXIT
};*/

enum GameMode
{
    NEW_GAME,
    LOAD_GAME
};

enum ExpForLevel //PH
{
    LEVEL_2     = 100,
    LEVEL_3     = 120,
    LEVEL_4     = 150,
    LEVEL_5     = 200,
    LEVEL_6     = 300,
    LEVEL_7     = 450,
    LEVEL_8     = 650,
    LEVEL_9     = 900,
    LEVEL_10    = 1200
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