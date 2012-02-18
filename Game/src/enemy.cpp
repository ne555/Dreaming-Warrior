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
#include "enemy.h"

Enemy::Enemy(int ID, int Atk, int Defense, int Health, int Level, string Name, int Wealth, int x, int y, string MapTexture, string Combat)
    : Creature(Atk, Defense, Health, x, y, Level, Name, Wealth), ID(ID), MapTextureFileName(MapTexture), Combat(Combat)
{
    CreatureMapTexture.LoadFromFile(MapTexture);
}

Enemy::Enemy(int ID, int Atk, int Defense, int Health, int Level, string Name, int Wealth, string Combat)
    : Creature(Atk, Defense, Health, Level, Name, Wealth), ID(ID), Combat(Combat)
{
}