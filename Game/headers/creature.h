#ifndef CREATURE_H
#define CREATURE_H

#include "include.h"
#include "spell.h"

class Creature
{
    int x;
    int y;
    int Level;
    int AttackPower; // Melee ili Spell Power
    int Armor;
    int MaxHealth;
    int MaxPower;
    int Health;
    int Power;
    int Wealth;
    std::string Name;

    std::vector<Buff> Buffs;

public:
    Creature() {}
    ~Creature() {}

    Creature(int Atk, int Armor, int Health, int x, int y, int Level, std::string Name)
        : AttackPower(Atk), Armor(Armor), Health(Health), MaxHealth(Health), x(x), y(y), Level(Level), Name(Name)
    {
    }
    Creature(int Atk, int Armor, int Health, int Level, std::string Name)
        : AttackPower(Atk), Armor(Armor), Health(Health), MaxHealth(Health), Level(Level), Name(Name)
    {
    }

    int GetX() const            { return x; }
    int GetY() const            { return y; }
    int GetLevel() const        { return Level; }
    int GetMaxHealth() const    { return MaxHealth; }
    int GetMaxPower() const     { return MaxPower; }
    int GetHealth() const       { return Health; }
    int GetPower() const        { return Power; }
    int GetAttackPower() const  { return AttackPower; }
    int GetArmor() const        { return Armor; }
    int GetWealth() const       { return Wealth; }
    std::string GetName() const { return Name;}

    const std::vector<Buff> &GetBuffs() const { return Buffs; }

    void SetX(int x)            { this->x = x; }
    void SetY(int y)            { this->y = y; }
    void SetLevel(int Level)    { this->Level = Level; }
    void SetMaxHealth(int MaxHealth) { this->MaxHealth = MaxHealth; }
    void SetMaxPower(int MaxPower) { this->MaxPower = MaxPower; }
    void SetHealth(int Health)  { this->Health = Health; }
    void SetPower(int Power)    { this->Power = Power; }
    void SetAttackPower(int Atk){ AttackPower = Atk; }
    void SetArmor(int Armor)    { this->Armor = Armor; }
    void SetWealth(int Wealth)  { this->Wealth = Wealth; }
    void SetName(std::string Name) { this->Name = Name; }

    void ApplyBuff(Buff Buff)
    {
        Buffs.push_back(Buff);
        switch(Buff.Attribute)
        {
        case HEALTH:
            SetMaxHealth(GetMaxHealth() + Buff.Value);
            SetHealth(GetHealth() + Buff.Value);
            break;
        case POWER:
            SetMaxPower(GetMaxPower() + Buff.Value);
            SetPower(GetPower() + Buff.Value);
            break;
        case ATTACK_POWER:
            break;
        case ARMOR:
            break;
        case INT_OR_STR:
            break;
        }
    }

    void RemoveBuffs()
    {
        for(auto itr = Buffs.begin(); itr != Buffs.end(); itr++)
        {
            switch(itr->Attribute)
            {
            case HEALTH:
                SetMaxHealth(GetMaxHealth() - itr->Value);
                if(GetHealth() > GetMaxHealth())
                    SetHealth(GetMaxHealth());
                continue;
            case POWER:
                SetMaxPower(GetMaxPower() - itr->Value);
                if(GetPower() > GetMaxPower())
                    SetPower(GetMaxPower());
                continue;
            case ATTACK_POWER:
                continue;
            case ARMOR:
                continue;
            case INT_OR_STR:
                continue;
            }
        }
        Buffs.clear();
    }
};

#endif