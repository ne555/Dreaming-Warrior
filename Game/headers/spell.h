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
#ifndef SPELL_H
#define SPELL_H


#include "include.h"
#include <SFML\Graphics.hpp>

struct Spell
{
    Spell(int ID, SpellType Type, string Name, int LevelReq, int Cost, int Value, string IconFileName = "NULL") 
        : Name(Name), Value(Value), Cost(Cost), Type(Type), ID(ID), LevelReq(LevelReq)
    {
        Icon.LoadFromFile(IconFileName);
    }
    sf::Texture Icon;
    SpellType Type;
    string Name;
    int Value;
    int Cost;
    int ID;
    int LevelReq;
};
/*
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
};*/

#endif