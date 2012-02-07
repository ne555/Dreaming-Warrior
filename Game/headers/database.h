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
Item GetItemFromDatabase(string World, int ID);
Quest GetQuestFromDatabase(string World, int ID);

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
        return ARMOR;
    case 5:
        return INT_OR_STR;
    }
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
        if(*itr == '_')
            *itr = ' ';
    return String;
}