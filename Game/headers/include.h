#ifndef INCLUDE_H
#define INCLUDE_H

#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

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

inline std::string IntToString(int Integer)
{
    std::stringstream convert;
    convert << Integer;
    return convert.str();
}

inline int StringToInt(std::string string)
{
    std::stringstream buffer(string);
    int a;
    buffer >> a;
    return a;
}

inline ItemType GetItemType(int Type)
{
    switch(Type)
    {
    case 0:
        return ITEM_QUEST;
    case 1:
        return ITEM_HEALTH_POTION;
    case 2:
        return ITEM_POWER_POTION;
    case 3:
        return ITEM_HEAD;
    case 4:
        return ITEM_SHOULDERS;
    case 5:
        return ITEM_CHEST;
    case 6:
        return ITEM_HANDS;
    case 7:
        return ITEM_LEGS;
    case 8:
        return ITEM_FOOT;
    case 9:
        return ITEM_MAINHAND;
    case 10:
        return ITEM_OFFHAND;
    }
}

inline Attribute GetAttribute(int Atr)
{
    switch(Atr)
    {
    case 0:
        return NO_ATTRIBUTE;
    case 1:
        return HEALTH;
    case 2:
        return POWER;
    case 3:
        return ATTACK_POWER;
    case 4:
        return ARMOR;
    case 5:
        return INT_OR_STR;
    }
}

enum CreatureType
{
    NO_CREATURE,
    RANDOM_ENEMY,
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

enum MainMenuResult
{
    DEFAULT_NEW,
    DEFAULT_LOAD,
    CUSTOM_NEW,
    CUSTOM_LOAD,
    EXIT
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