#ifndef SPELL_H
#define SPELL_H


#include "include.h"
#include <SFML\Graphics.hpp>

struct Castable
{
    Castable(string Name, int Value, int Cost) : Name(Name), Value(Value), Cost(Cost) {}
    string Name;
    int Value;
    int Cost;
};

struct Buff : public Castable
{
    Buff(string Name, Attribute Attribute, int Value, int Cost) : Castable(Name, Value, Cost) 
    {
        this->Attribute = Attribute;
    }
    Attribute Attribute;
};

struct Spell : public Castable
{
    Spell(SpellType Type, string Name, int Value, int Cost, string IconFileName = "NULL") : Castable(Name, Value, Cost)
    {
        this->Type = Type;
        Icon.LoadFromFile(IconFileName);
    }

    sf::Texture Icon;
    SpellType Type;
};

#endif