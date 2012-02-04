#ifndef ENEMY_H
#define ENEMY_H

struct Enemy;

#include "vector"
#include "item.h"
#include "creature.h"

struct Enemy : public Creature
{
    Enemy(int Atk, int Def, int Health, int x, int y, std::string Alive, std::string Combat, int Level, std::string Name);
    Enemy(int Atk, int Def, int Health, std::string Combat, int Level, std::string Name);
    ~Enemy();

    // i igrac ima slicno
    sf::Texture CreatureMapTexture;
    sf::Texture CreatureCombatTexture;

    //TODO: U DB loot i pare
    struct Loot
    {
        Loot(Item Item, int Chance) : Item(Item), Chance(Chance) {}
        int Chance;
        Item Item;
    };
    std::vector<Loot> Loot;
};

#endif