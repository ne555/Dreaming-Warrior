#include "enemy.h"

Enemy::Enemy(int Atk, int Armor, int Health, int x, int y, std::string MapTexture, std::string Combat, int Level, std::string Name)
    : Creature(Atk, Armor, Health, x, y, Level, Name)
{
    CreatureMapTexture.LoadFromFile(MapTexture);
    CreatureCombatTexture.LoadFromFile(Combat);
}

Enemy::Enemy(int Atk, int Armor, int Health, std::string Combat, int Level, std::string Name)
    : Creature(Atk, Armor, Health, Level, Name)
{
    CreatureCombatTexture.LoadFromFile(Combat);
}

Enemy::~Enemy()
{
}