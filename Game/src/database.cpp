#include <SFML\Graphics.hpp>
#include "item.h"
#include "quest.h"

void SetSpaces(std::string &String)
{
    for(auto itr = String.begin(); itr != String.end(); itr++)
    {
        if(*itr == '_')
            *itr = ' ';
    }
}

Item GetItemFromDatabase(int ID)
{
    Item Item;
    std::ifstream file("ItemDatabase.txt");
    std::string line, buffer;
    while(getline(file, line))
    {
        auto itr = line.begin();

        //Check for right item
        while(*itr != ' ')
            buffer += *itr;
        if(StringToInt(buffer) != ID)
            continue;
        ++itr;
        buffer.clear();

        //Set Item Type
        while(*itr != ' ')
            buffer += *itr;
        Item.Type = GetItemType(StringToInt(buffer));
        ++itr;
        buffer.clear();

        //Set Name
        while(*itr != ' ')
            buffer += *itr;
        SetSpaces(buffer);
        Item.Name = buffer;
        ++itr;
        buffer.clear();

        //Set Image
        while(*itr != ' ')
            buffer += *itr;
        Item.Visual.LoadFromFile(buffer);
        ++itr;
        buffer.clear();

        //Check if Item is quest item
        if(Item.Type == ITEM_QUEST)
            return Item;

        //Set Price
        while(*itr != ' ')
            buffer += *itr;
        Item.BuyPrice = StringToInt(buffer);
        ++itr;
        buffer.clear();
        while(*itr != ' ')
            buffer += *itr;
        Item.SellPrice = StringToInt(buffer);

        //Check if item is potion
        if(Item.Type == ITEM_HEALTH_POTION || Item.Type == ITEM_POWER_POTION)
        {
            while(*itr != ' ')
                buffer += *itr;
            Item.Value = StringToInt(buffer);
            return Item;
        }

        //Set attributes
        while(itr != line.end())
        {
            while(*itr != ' ')
                buffer += *itr;
            Attribute Attribute = GetAttribute(StringToInt(buffer));
            while(*itr != ' ')
                buffer += *itr;
            Item.Attributes.push_back(ItemAttribute(Attribute, StringToInt(buffer)));
        }
    }
    return Item;
}

Quest GetQuestFromDatabase(int ID)
{
    Quest Quest;
    std::ifstream file("QuestDatabase.txt");
    std::string line, buffer;
    while(getline(file, line))
    {
        auto itr = line.begin();

        //Check for right quest
        while(*itr != ' ')
            buffer += *itr;
        if(StringToInt(buffer) != ID)
            continue;
        ++itr;
        buffer.clear();

        //Set name
        while(*itr != ' ')
            buffer += *itr;
        Quest.Name = buffer;
        ++itr;
        buffer.clear();

        //Set story
        while(*itr != ' ')
            buffer += *itr;
        SetSpaces(buffer);
        Quest.Text = buffer;
        ++itr;
        buffer.clear();

        //Set Requirements
        while(*itr != ' ')
            buffer += *itr;
        Quest.LevelReq = StringToInt(buffer);
        ++itr;
        buffer.clear();
        while(*itr != ' ')
            buffer += *itr;
        Quest.QuestReq = StringToInt(buffer);
        ++itr;
        buffer.clear();

        //Set objectives
        while(itr != line.end())
        {
            //TODO
        }
    }
    return Quest;
}