#ifndef ITEM_H
#define ITEM_H

struct ItemAttribute;
struct Item;

#include "Include.h"
#include <SFML\Graphics.hpp>

/*
TODO:
buy/sell price
*/
struct Item
{
    struct ItemAttribute
    {
        ItemAttribute(Attribute Attribute, int Value) : Attribute(Attribute), Value(Value) {}
        int Value;
        Attribute Attribute;
    };

    // Opæi constructor
    Item(ItemType Type, std::string Name, std::string ImageFileName) : Type(Type)
    {
        Visual.LoadFromFile(ImageFileName);
    }
    // Napitak constructor
    Item(ItemType Type, std::string Name, std::string ImageFileName, int Value) : Type(Type), Value(Value)
    {
        Visual.LoadFromFile(ImageFileName);
    }

    //ovo moze bit odma hendlano
    void AddAttribute(Attribute Attribute, int Value)
    {
        Attributes.push_back(ItemAttribute(Attribute, Value));
    }

    ItemType Type;
    std::string Name;
    sf::Texture Visual;
    int Value; // U slucaju napitaka
    std::vector<ItemAttribute> Attributes;
};

#endif