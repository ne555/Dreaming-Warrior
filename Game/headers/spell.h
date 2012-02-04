#ifndef SPELL_H
#define SPELL_H


#include "include.h"
#include <SFML\Graphics.hpp>

struct Castable
{
    Castable(std::string Name, int Value, int Cost) : Name(Name), Value(Value), Cost(Cost) {}
    std::string Name;
    int Value;
    int Cost;
};

struct Buff : public Castable
{
    Buff(std::string Name, Attribute Attribute, int Value, int Cost) : Castable(Name, Value, Cost) 
    {
        this->Attribute = Attribute;
    }
    Attribute Attribute;
};

struct Spell : public Castable
{
    Spell(SpellType Type, std::string Name, int Value, int Cost, std::string IconFileName = "NULL") : Castable(Name, Value, Cost)
    {
        this->Type = Type;
        Icon.LoadFromFile(IconFileName);
    }

    sf::Texture Icon;
    SpellType Type;
};

#endif