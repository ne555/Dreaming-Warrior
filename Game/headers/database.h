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
    for(auto itr = String.begin(); itr != String.end(); itr++)
        if(*itr == '_')
            *itr = ' ';
    return String;
}