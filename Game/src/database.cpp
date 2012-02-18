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
#include "item.h"
#include "quest.h"
#include "spell.h"
#include "database.h"

/*
TODO: 
- Pojednostaviti GetItemFromDatabse()
*/

Item GetItemFromDatabase(string World, int ID)
{
    Item Item;
    std::ifstream file(World + "/ItemDatabase.txt");
    string line, buffer;
    while(getline(file, line))
    {
        auto itr = line.begin();

        //Check for right item
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Item.ID = StringToInt(buffer);
        if(Item.ID != ID)
            continue;
        ++itr;
        buffer.clear();

        //Set Item Type
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Item.Type = GetItemType(StringToInt(buffer));
        ++itr;
        buffer.clear();

        //Set Name
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Item.Name = SetSpaces(buffer);
        ++itr;
        buffer.clear();

        //Set Image
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Item.ItemTexture.LoadFromFile(buffer);
        ++itr;
        buffer.clear();

        //Check if Item is quest item
        if(Item.Type == ITEM_QUEST)
            return Item;

        //Set Price
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Item.BuyPrice = StringToInt(buffer);
        ++itr;
        buffer.clear();
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Item.SellPrice = StringToInt(buffer);
        ++itr;
        buffer.clear();
        //Check if item is potion
        if(Item.Type == ITEM_HEALTH_POTION || Item.Type == ITEM_POWER_POTION)
        {
            while(*itr != ' ')
            {
                buffer += *itr;
                ++itr;
            }
            Item.Value = StringToInt(buffer);
            return Item;
        }

        //Set attributes
        --itr;
        while(itr != line.end())
        {
            ++itr;
            while(*itr != ' ')
            {
                buffer += *itr;
                ++itr;
            }
            Attribute Attribute = GetAttribute(StringToInt(buffer));
            ++itr;
            buffer.clear();
            while(*itr != ' ' && itr != line.end())
            {
                buffer += *itr;
                ++itr;
            }
            Item.Attributes.push_back(ItemAttribute(Attribute, StringToInt(buffer)));
            buffer.clear();
        }
        return Item;
    }
    cerr << "FATAL: Invalid item ID." << endl;
    exit(1);
}

Quest GetQuestFromDatabase(string World, int ID)
{
    std::ifstream File(World + "/QuestDatabase.txt");
    int QID, StartCreature, EndCreature, Level_req, Quest_req, Num_Obj;
    string Name, Text;
    while(File >> QID >> StartCreature >> EndCreature >> Name >> Text >> Level_req >> Quest_req >> Num_Obj)
    {
        if(QID != ID)
        {
             File.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             continue;
        }
        Quest Quest(ID, StartCreature, EndCreature, SetSpaces(Name), SetSpaces(Text), Level_req, Quest_req, Num_Obj);
        for(int a = 0; a<Num_Obj; ++a)
        {
            int obj, obj_id, count;
            string map;
            File >> obj;
            switch(obj)
            {
            case 0:
                File >> map >> obj_id >> count;
                Quest.Objectives.push_back(QuestObjective(GetQuestType(obj), count, obj_id, map, 0));
                break;
            case 1:
                File >> obj_id >> count;
                Quest.Objectives.push_back(QuestObjective(GetQuestType(obj), count, obj_id));
                break;
            }
        }
        File >> ID;
        Quest.ItemReward = ID;
        return Quest;
    }
    cerr << "FATAL: Invalid quest ID." << endl;
    exit(1);
}

Spell GetSpellFromDatabase(string World, int ID)
{
    std::ifstream File(World + "/SpellDatabase.txt");
    int SID, type, LevelReq, Cost, Value;
    string Name;
    while(File >> SID >> type >> Name >> LevelReq >> Cost >> Value)
    {
        if(SID != ID)
            continue;
        Spell Spell(ID, GetSpellType(type), Name, LevelReq, Cost, Value);
        return Spell;
    }
    cerr << "FATAL: Invalid spell ID." << endl;
    exit(1);
}

//todo ovo treba biti prije loadano u poseban string u questu
string GetEnemyNameFromDatabase(string Map, int ID)
{
    std::ifstream File(Map + "Enemies.txt");
    int CID;
    string trash, Name;
    while(File >> CID >> trash >> trash >> trash >> trash >> Name >> trash >> trash >> trash >> trash
        >> trash >> trash >> trash >> trash >> trash >> trash >> trash >> trash)
    {
        if(CID == ID)
        {
            return SetSpaces(Name);
        }
    }
    File.close();
    File.open(Map + "RandomEncounters.txt");
    while(File >> CID >> trash >> trash >> trash >> trash >> Name >> trash)
    {
        if(CID == ID)
            return SetSpaces(Name);
    }
    cerr << "FATAL: Invalid enemy ID." << endl;
    exit(1);
}