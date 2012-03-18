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
#ifndef ENEMY_H
#define ENEMY_H

#include "vector"
#include "item.h"
#include "creature.h"

struct Loot
{
    Loot(Item Item, int Chance) : Item(Item), Chance(Chance) {}
    int Chance;
    Item Item;
};

struct Enemy : public Creature
{
    Enemy(int ID, int Atk, int Def, int Health, int Level, string Name, int Wealth, int x, int y, string MapTexture, string Combat)
        : Creature(Atk, Def, Health, x, y, Level, Name, Wealth), ID(ID), MapTextureFileName(MapTexture), Combat(Combat)
    {
        CreatureMapTexture.loadFromFile(MapTexture);
    }
    Enemy(int ID, int Atk, int Def, int Health, int Level, string Name, int Wealth, string Combat)
        : Creature(Atk, Def, Health, Level, Name, Wealth), ID(ID), Combat(Combat)
    {
    }

    sf::Texture CreatureMapTexture;
    string MapTextureFileName;
    string Combat;

    int ID;
    vector<Loot> Loot;
};

#endif