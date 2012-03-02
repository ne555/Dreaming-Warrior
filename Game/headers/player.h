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
#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "item.h"
#include "quest.h"

class Player : public Creature
{
    vector<Item> Items;
    vector<Item> EquipedItems;
    vector<Spell> Spells;
    vector<Quest> Quests;
    vector<int> CompletedQuests;

    Class PlayerClass;
    int Exp;
    int IntStr; // Intelligence / Strength
    int TalentPoints;

public:
    Class LoadFromFile(string World, Class ClassHack, bool ThisIsHack, string Name);

    ObjectType InteractsWith;
    string Map;

    int GetIntStr() const   { return IntStr; }
    Class GetClass() const  { return PlayerClass; }
    int GetExp() const      { return Exp; }
    int GetTalentPoints() const { return TalentPoints; }

    void SetIntStr(int IntStr) { this->IntStr = IntStr; }
    void UseTalentPoint() { --TalentPoints; }
    void IncrementExp() 
    { 
        Exp += 1; 
        if(Exp == 10)
        {
            SetLevel(GetLevel()+1); 
            Exp = 0;
            TalentPoints += 3;
        }
    }

    const vector<Spell> &GetSpells() const { return Spells; }
    const vector<Item> &GetEquipedItems() const { return EquipedItems; }
    const vector<Item> &GetItems() const { return Items; }
    vector<Quest> &GetQuests() { return Quests; }
    vector<int> GetCompletedQuests() const { return CompletedQuests; }

    int GetHealthPotNum()
    {
        int NumHealthPots = 0;

        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
            if(itr->Type == ITEM_HEALTH_POTION)
                NumHealthPots++;

        return NumHealthPots;
    }

    int GetPowerPotNum()
    {
        int NumManaPots = 0;

        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
            if(itr->Type == ITEM_POWER_POTION)
                NumManaPots++;

        return NumManaPots;
    }

    /*
    TODO: Ove dvije po IDU jer ce biti vise vrsta potova?
    */
    bool UseHealthPotIfCan()
    {
        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
        {
            if(itr->Type == ITEM_HEALTH_POTION)
            {
                SetHealth(GetHealth()+itr->Value);
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
            if(itr->Type == ITEM_POWER_POTION)
            {
                SetPower(GetPower() + itr->Value);
                Items.erase(itr);
                return true;
            }
        }
        return false;
    }

    bool AddItem(Item Item, bool IsEquiped = false)
    {
        if(Items.size() <= MAX_ITEMS)
        {
            IsEquiped ? EquipedItems.push_back(Item) : Items.push_back(Item);
            return true;
        }
        else
            return false;
    }

    void EquipItem(int ID) //todo nevalja bre
    {
        for(auto itr = Items.begin(); itr != Items.end(); ++itr)
        {
            if(itr->ID == ID)
            {
                EquipedItems.push_back(*itr);
                Items.erase(itr);
                return;
            }
        }
    }

    void EquipItem(Item Item)
    {
        for(auto itr = EquipedItems.begin(); itr != EquipedItems.end(); ++itr)
        {
            if(itr->Type == Item.Type)
            {
                Items.push_back(*itr);
                for(auto atr_itr = itr->Attributes.begin(); atr_itr != itr->Attributes.end(); ++atr_itr)
                {
                    switch(atr_itr->Attribute)
                    {
                    case HEALTH:
                        SetMaxHealth(GetMaxHealth() - atr_itr->Value);
                        continue;
                    case POWER:
                        SetMaxPower(GetMaxPower() - atr_itr->Value);
                        continue;
                    case ATTACK_POWER:
                        SetAttack(GetAttack() - atr_itr->Value);
                        continue;
                    case DEFENSE_POWER:
                        SetDefense(GetDefense() - atr_itr->Value);
                        continue;
                    case INT_OR_STR:
                        SetIntStr(GetIntStr() - atr_itr->Value);
                        continue;
                    }
                }
                EquipedItems.erase(itr);
                break;
            }
        }
        EquipedItems.push_back(Item);
        CalculateStatsFromEquip();
    }

    void RemoveItem(int Iter)
    {
        auto itr = Items.begin() + Iter;
        Items.erase(itr);
    }

    void CalculateStatsFromEquip()
    {
        for(auto itr = EquipedItems.begin(); itr != EquipedItems.end(); ++itr)
        {
            for(auto iter = itr->Attributes.begin(); iter != itr->Attributes.end(); ++iter)
            {
                switch(iter->Attribute)
                {
                case HEALTH:
                    SetMaxHealth(GetMaxHealth() + iter->Value);
                    SetHealth(GetHealth() + iter->Value);
                    continue;
                case POWER:
                    SetMaxPower(GetMaxPower() + iter->Value);
                    SetPower(GetPower() + iter->Value);
                    continue;
                case ATTACK_POWER:
                    SetAttack(GetAttack() + iter->Value);
                    continue;
                case DEFENSE_POWER:
                    SetDefense(GetDefense() + iter->Value);
                    continue;
                case INT_OR_STR:
                    SetIntStr(GetIntStr() + iter->Value);
                    continue;
                }
            }
        }
    }

    void AddSpell(Spell Spell)
    {
        Spells.push_back(Spell);
    }

    void AddQuest(Quest Quest)
    {
        Quests.push_back(Quest);
    }

    void AddCompletedQuest(int ID)
    {
        CompletedQuests.push_back(ID);
    }

    bool HasCompletedQuest(int ID)
    {
        for(auto itr = CompletedQuests.begin(); itr != CompletedQuests.end(); ++itr)
        {
            if(*itr == ID)
                return true;
        }
        return false;
    }

    void RemoveQuest(int ID)
    {
        for(auto itr = Quests.begin(); itr != Quests.end(); ++itr)
        {
            if(itr->ID == ID)
            {
                Quests.erase(itr);
                return;
            }
        }
    }

    void UpdateQuestObjective(int ID)
    {
        for(auto itr = Quests.begin(); itr != Quests.end(); ++itr)
            if(itr->Objective.ReqProgress != itr->Objective.CurrentProgress)
                itr->Objective.CurrentProgress += 1;
    }
};

#endif