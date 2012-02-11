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
    Enemy(int ID, int Atk, int Def, int Health, string Combat, int Level, string Name, int Wealth, int x, int y, string MapTexture);
    Enemy(int ID, int Atk, int Def, int Health, string Combat, int Level, string Name, int Wealth);
    ~Enemy();

    // i igrac ima slicno
    sf::Texture CreatureMapTexture;
    sf::Texture CreatureCombatTexture;
    string MapTextureFileName;
    string CombatTextureFileName;

    int ID;
    vector<Loot> Loot;
};

#endif