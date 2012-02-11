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
#include "enemy.h"

Enemy::Enemy(int ID, int Atk, int Armor, int Health, string Combat, int Level, string Name, int Wealth, int x, int y, string MapTexture)
    : Creature(Atk, Armor, Health, x, y, Level, Name, Wealth), ID(ID), CombatTextureFileName(Combat), MapTextureFileName(MapTexture)
{
    CreatureMapTexture.LoadFromFile(MapTexture);
    CreatureCombatTexture.LoadFromFile(Combat);
}

Enemy::Enemy(int ID, int Atk, int Armor, int Health, string Combat, int Level, string Name, int Wealth)
    : Creature(Atk, Armor, Health, Level, Name, Wealth), ID(ID), CombatTextureFileName(Combat)
{
    CreatureCombatTexture.LoadFromFile(Combat);
}

Enemy::~Enemy()
{
}