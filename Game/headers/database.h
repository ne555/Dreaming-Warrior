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
Item GetItemFromDatabase(const string World, int ID);
Quest GetQuestFromDatabase(const string World, int ID);
Spell GetSpellFromDatabase(const string World, int ID);

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
        return ITEM_CHEST;
    case 5:
        return ITEM_HANDS;
    case 6:
        return ITEM_LEGS;
    case 7:
        return ITEM_FOOT;
    case 8:
        return ITEM_WEAPON;
    case 9:
        return ITEM_SHIELD;
    case 10:
        return ITEM_FOOD;
    }
    cerr << "FATAL: Invalid item type." << endl;
    exit(1);
}

inline Class GetPlayerClass(int ID)
{
    switch(ID)
    {
    case 0:
        return CLASS_WARRIOR;
    case 1:
        return CLASS_MAGE;
    }
    cerr << "FATAL: Invalid class ID." << endl;
    exit(1);
}

inline QuestType GetQuestType(int ID)
{
    if(ID == 0)
        return KILL;
    else 
        return ITEM;
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
        return DEFENSE_POWER;
    case 5:
        return INT_OR_STR;
    }
    cerr << "FATAL: Invalid attribute ID." << endl;
    exit(1);
}

inline SpellType GetSpellType(int Type)
{
    switch(Type)
    {
    case 0:
        return SPELL_ATTACK;
    case 1:
        return SPELL_HEAL;
    }
    cerr << "FATAL: Invalid spell type." << endl;
    exit(1);
}

inline int StringToInt(string string)
{
    stringstream buffer(string);
    int a;
    buffer >> a;
    return a;
}

inline string SetSpaces(string String)
{
    for(auto itr = String.begin(); itr != String.end(); ++itr)
    {
        if(*itr == '_')
        {
            *itr = ' ';
        }
        else if(*itr == '%')
        {
            *itr = '\n';
        }
    }
    return String;
}