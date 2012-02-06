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

    int ID;
    vector<Loot> Loot;
};

#endif