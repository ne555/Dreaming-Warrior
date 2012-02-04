#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "item.h"
#include "quest.h"

class Player : public Creature
{
    std::vector<Item*> Items;
    std::vector<Item*> EquipedItems;
    std::vector<Castable> Spells;
    std::vector<Quest> Quests;

    Class PlayerClass;
    int Exp;
    int IntStr; // Inteligence / Strength
    int NumItems; // Broj Itema ili Stackova Itema

public:
    Player();
    ~Player();

    void LoadFromFile(std::string LoadFileName);

    CreatureType InteractsWith;

    int GetIntStr() const   { return IntStr; }
    Class GetClass() const  { return PlayerClass;}

    void SetIntStr(int IntStr) { this->IntStr = IntStr; }

    const std::vector<Castable> &GetSpells() const { return Spells; }
    const std::vector<Item*> &GetEquipedItems() const { return EquipedItems; }
    const std::vector<Item*> &GetItems() const { return Items; }

    int GetHealthPotNum()
    {
        int NumHealthPots = 0;

        for(auto iter = Items.begin(); iter != Items.end(); iter++)
            if((*iter)->Type == ITEM_HEALTH_POTION)
                NumHealthPots++;

        return NumHealthPots;
    }

    int GetPowerPotNum()
    {
        int NumManaPots = 0;

        for(auto iter = Items.begin(); iter != Items.end(); iter++)
            if((*iter)->Type == ITEM_POWER_POTION)
                NumManaPots++;

        return NumManaPots;
    }

    /*
    TODO: Ove dvije po imenu jer ce biti vise vrsta potova
    */
    bool UseHealthPotIfCan()
    {
        for(auto iter = Items.begin(); iter != Items.end(); iter++)
        {
            if((*iter)->Type == ITEM_HEALTH_POTION)
            {
                SetHealth(GetHealth()+(*iter)->Value);
                if(GetHealth() > GetMaxHealth())
                    SetHealth(GetMaxHealth());
                delete *iter;
                Items.erase(iter);
                return true;
            }
        }
        return false;
    }

    bool UsePowerPotIfCan()
    {
        for(auto iter = Items.begin(); iter != Items.end(); iter++)
        {
            if((*iter)->Type == ITEM_POWER_POTION)
            {
                SetPower(GetPower() + (*iter)->Value);
                if(GetPower() > GetMaxPower())
                    SetPower(GetMaxPower());
                delete *iter;
                Items.erase(iter);
                return true;
            }
        }
        return false;
    }

    bool AddItem(Item* Item)
    {
        if(NumItems < BACKPACK_SIZE)
        {
            Items.push_back(Item);
            NumItems++;
            return true;
        }
        else
            return false;
    }

    // Zamjena itema
    void EquipItem(std::vector<Item*>::iterator newItem)
    {
        for(auto oldItem = EquipedItems.begin(); oldItem != Items.end(); oldItem++)
        {
            if((*oldItem)->Type == (*newItem)->Type)
            {
                //swap? ovdje mozda mem leak
                //ovdje su ozbiljni problemi s leakom
                Item* pOld = *oldItem;
                Item* pNew = *newItem;
                delete *oldItem;
                EquipedItems.erase(oldItem);
                EquipedItems.push_back(pNew);
                delete *newItem;
                Items.erase(newItem);
                Items.push_back(pOld);
                CalculateStatsFromEquip();
                return;
            }
        }
    }

    // Novi item (na ucitavanju igre)
    void EquipItem(Item* Item)
    {
        EquipedItems.push_back(Item);
    }

    void RemoveItem(std::string Name)
    {
        for(auto itr = Items.begin(); itr != Items.end(); itr++)
        {
            if((*itr)->Name == Name)
            {
                delete *itr;
                Items.erase(itr);
                return;
            }
        }
    }

    void CalculateStatsFromEquip()
    {
        for(auto itr = EquipedItems.begin(); itr != EquipedItems.end(); itr++)
        {
            for(auto iter = (*itr)->Attributes.begin(); iter != (*itr)->Attributes.end(); iter++)
            {
                switch(iter->Attribute)
                {
                case HEALTH:
                    SetMaxHealth(GetMaxHealth() + iter->Value);
                    continue;
                case POWER:
                    SetMaxPower(GetMaxPower() + iter->Value);
                    continue;
                case ATTACK_POWER:
                    SetAttackPower(GetAttackPower() + iter->Value);
                    continue;
                case ARMOR:
                    SetArmor(GetArmor() + iter->Value);
                    continue;
                case INT_OR_STR:
                    SetIntStr(GetIntStr() + iter->Value);
                    continue;
                }
            }
        }
    }

    void AddSpell(Castable Spell)
    {
        Spells.push_back(Spell);
    }
};

#endif