#include "item.h"
#include "quest.h"
#include "database.h"

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
        Item.Visual.LoadFromFile(buffer);
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
}

Quest GetQuestFromDatabase(string World, int ID)
{
    Quest Quest;
    std::ifstream file(World + "/QuestDatabase.txt");
    string line, buffer;
    while(getline(file, line))
    {
        auto itr = line.begin();

        //Check for right quest
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        if(StringToInt(buffer) != ID)
            continue;
        ++itr;
        buffer.clear();

        //Set name
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Quest.Name = buffer;
        ++itr;
        buffer.clear();

        //Set story
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        SetSpaces(buffer);
        Quest.Text = buffer;
        ++itr;
        buffer.clear();

        //Set Requirements
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Quest.LevelReq = StringToInt(buffer);
        ++itr;
        buffer.clear();
        while(*itr != ' ')
        {
            buffer += *itr;
            ++itr;
        }
        Quest.QuestReq = StringToInt(buffer);
        ++itr;
        buffer.clear();

        //Set objectives
        while(itr != line.end())
        {
            QuestObjective Objective;
            //Set objective type
            buffer += *itr;
            ++itr;
            switch(StringToInt(buffer))
            {
                //Kill
            case 0:
                Objective.Type = KILL;
                break;
                //Collect
            case 1:
                Objective.Type = ITEM;
                break;
            }
            buffer.clear();
            //Set ID of a quest or item requirement
            while(*itr != ' ')
            {
                 buffer += *itr;
                 ++itr;
            }
            Objective.ID = StringToInt(buffer);
            buffer.clear();
            //Set count
            while(*itr != ' ')
            {
                buffer += *itr;
                ++itr;
            }
            Objective.ReqProgress = StringToInt(buffer);
            Objective.CurrentProgress = 0;
            Quest.Objectives.push_back(Objective);
        }
    }
    return Quest;
}