#ifndef COMBAT_H
#define COMBAT_H

class Player;

#include "enemy.h"

class Combat
{
    sf::RenderWindow &window;
    Player &player;
    Enemy enemy;

    std::vector<sf::Text> CombatTexts;
    float TextY;

    void DrawPlayerStats();
    void DrawCommandText(int WhatText);

    void CreatureAttack();
    void MeleeAttack();
    bool SpellCast(const Spell &Spell, Creature &Caster, Creature &Target);
    bool SpellCast(const Buff &Buff, Creature &Caster, Creature &Target);
    bool RunIfCan();
    void DropLoot();

    bool HandleInput(int &CommandList, int &Command, float &ArrowY, bool &PlayerMove);
    void HandleCombatText(std::string CombatString);

public:
    Combat(sf::RenderWindow &window, Player &player, Enemy enemy);
    ~Combat();
    int MainLoop();
};

#endif