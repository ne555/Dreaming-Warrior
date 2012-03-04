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
#ifndef SPELL_H
#define SPELL_H


#include "include.h"
#include <SFML\Graphics.hpp>

struct Spell
{
    Spell(int ID, SpellType Type, string Name, int LevelReq, int Cost, int Value) 
        : Name(Name), Value(Value), Cost(Cost), Type(Type), ID(ID), LevelReq(LevelReq)
    {
    }
    SpellType Type;
    string Name;
    int Value;
    int Cost;
    int ID;
    int LevelReq;
};

#endif