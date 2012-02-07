/*
    This file is part of Game Project.

    Game Project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Game Project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Game Project.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "item.h"
#include "quest.h"

class Player : public Creature
{
    vector<Item*> Items;
    vector<Item*> EquipedItems;
    vector<Castable> Spells;
    vector<Quest> Quests;

    Class PlayerClass;
    int Exp;
    int IntStr; // Inteligence / Strength
    int NumItems; // Broj Itema ili Stackova Itema

public:
    Player();
    ~Player();

    void LoadFromFile(string LoadFileName);

    ObjectType InteractsWith;

    int GetIntStr() const   { return IntStr; }
    Class GetClass() const  { return PlayerClass;}

    void SetIntStr(int IntStr) { this->IntStr = IntStr; }

    const vector<Castable> &GetSpells() const { return Spells; }
    const vector<Item*> &GetEquipedItems() const { return EquipedItems; }
    const vector<Item*> &GetItems() const { return Items; }

    int GetHealthPotNum()
    {
        int NumHealthPots = 0;

        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
            if((*itr)->Type == ITEM_HEALTH_POTION)
                NumHealthPots++;

        return NumHealthPots;
    }

    int GetPowerPotNum()
    {
        int NumManaPots = 0;

        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
            if((*itr)->Type == ITEM_POWER_POTION)
                NumManaPots++;

        return NumManaPots;
    }

    /*
    TODO: Ove dvije po imenu jer ce biti vise vrsta potova
    */
    bool UseHealthPotIfCan()
    {
        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
        {
            if((*itr)->Type == ITEM_HEALTH_POTION)
            {
                SetHealth(GetHealth()+(*itr)->Value);
                if(GetHealth() > GetMaxHealth())
                    SetHealth(GetMaxHealth());
                delete *itr;
                Items.erase(itr);
                return true;
            }
        }
        return false;
    }

    bool UsePowerPotIfCan()
    {
        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
        {
            if((*itr)->Type == ITEM_POWER_POTION)
            {
                SetPower(GetPower() + (*itr)->Value);
                if(GetPower() > GetMaxPower())
                    SetPower(GetMaxPower());
                delete *itr;
                Items.erase(itr);
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
    void EquipItem(vector<Item*>::iterator newItem)
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

    void RemoveItem(string Name)
    {
        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
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
        for(auto itr = EquipedItems.begin(); itr != EquipedItems.end(); ++itr)
        {
            for(auto iter = (*itr)->Attributes.begin(); iter != (*itr)->Attributes.end(); ++itr)
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