#include "enemy.h"

Enemy::Enemy(int ID, int Atk, int Armor, int Health, string Combat, int Level, string Name, int Wealth, int x, int y, string MapTexture)
    : Creature(Atk, Armor, Health, x, y, Level, Name, Wealth), ID(ID)
{
    CreatureMapTexture.LoadFromFile(MapTexture);
    CreatureCombatTexture.LoadFromFile(Combat);
}

Enemy::Enemy(int ID, int Atk, int Armor, int Health, string Combat, int Level, string Name, int Wealth)
    : Creature(Atk, Armor, Health, Level, Name, Wealth), ID(ID)
{
    CreatureCombatTexture.LoadFromFile(Combat);
}

Enemy::~Enemy()
{
}