#ifndef ITEM_H
#define ITEM_H

#include "Include.h"
#include <SFML\Graphics.hpp>

struct ItemAttribute
{
    ItemAttribute(Attribute Attribute, int Value) : Attribute(Attribute), Value(Value) {}
    int Value;
    Attribute Attribute;
};

struct Item
{
    int ID;
    ItemType Type;
    string Name;
    sf::Texture Visual;
    int Value;
    int BuyPrice;
    int SellPrice;
    vector<ItemAttribute> Attributes;
};

#endif