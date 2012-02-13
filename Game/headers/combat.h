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
#ifndef COMBAT_H
#define COMBAT_H

class Player;

#include "enemy.h"

class Combat
{
    sf::RenderWindow &window;
    Player &player;
    Enemy enemy;

    vector<sf::Text> CombatTexts;
    float TextY;

    void DrawPlayerStats();
    void DrawCommandText(int WhatText);

    void CreatureAttack();
    void MeleeAttack();
    bool SpellCast(const Spell &Spell, Creature &Caster, Creature &Target);
    //bool SpellCast(const Buff &Buff, Creature &Caster, Creature &Target);
    bool RunIfCan();
    void DropLoot();

    bool HandleInput(int &CommandList, int &Command, float &ArrowY, bool &PlayerMove);
    void HandleCombatText(string CombatString);

public:
    Combat(sf::RenderWindow &window, Player &player, Enemy enemy);
    int MainLoop();
};

#endif