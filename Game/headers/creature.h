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
#ifndef CREATURE_H
#define CREATURE_H

#include "include.h"
#include "spell.h"

class Creature
{
    int x;
    int y;
    int Level;
    int Attack; // Melee ili Spell Power
    int Defense;
    int MaxHealth;
    int MaxPower;
    int Health;
    int Power;
    int Wealth;
    string Name;

public:
    Creature() {}
    ~Creature() {}

    Creature(int Atk, int Defense, int Health, int x, int y, int Level, string Name, int Wealth)
        : Attack(Atk), Defense(Defense), Health(Health), MaxHealth(Health), x(x), y(y), Level(Level), Name(Name), Wealth(Wealth)
    {
    }
    Creature(int Atk, int Defense, int Health, int Level, string Name, int Wealth)
        : Attack(Atk), Defense(Defense), Health(Health), MaxHealth(Health), Level(Level), Name(Name), Wealth(Wealth)
    {
    }

    int GetX() const            { return x; }
    int GetY() const            { return y; }
    int GetLevel() const        { return Level; }
    int GetMaxHealth() const    { return MaxHealth; }
    int GetMaxPower() const     { return MaxPower; }
    int GetHealth() const       { return Health; }
    int GetPower() const        { return Power; }
    int GetAttack() const       { return Attack; }
    int GetDefense() const      { return Defense; }
    int GetWealth() const       { return Wealth; }
    string GetName() const      { return Name;}

    void SetX(int x)            { this->x = x; }
    void SetY(int y)            { this->y = y; }
    void SetLevel(int Level)    { this->Level = Level; }
    void SetMaxHealth(int MaxHealth) { this->MaxHealth = MaxHealth;}
    void SetMaxPower(int MaxPower) { this->MaxPower = MaxPower; }
    void SetHealth(int Health)  { this->Health = Health; if(this->Health > MaxHealth) this->Health = MaxHealth; }
    void SetPower(int Power)    { this->Power = Power; if(this->Power > MaxPower) this->Power = MaxPower; }
    void SetAttack(int Atk){ Attack = Atk; }
    void SetDefense(int Defense){ this->Defense = Defense; }
    void SetWealth(int Wealth)  { this->Wealth = Wealth; }
    void SetName(string Name)   { this->Name = Name; }
};

#endif