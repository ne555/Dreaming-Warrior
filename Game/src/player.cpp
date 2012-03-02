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
#include "player.h"
#include "database.h"

Class Player::LoadFromFile(string World, Class ClassHack, bool ThisIsHack, string Name)
{
    std::ifstream File(World + "/Player.txt");
    int x, y, level, exp, int_str, health, power, attack, Defense, id, _class, talent_pts, wealth;
    string name, map;
    File >> map >> x >> y >> wealth >> name >> _class >> level >> exp >> talent_pts >> int_str >> health >> power >> attack >> Defense;
    Map = map;
    SetX(x);
    SetY(y);
    SetName(SetSpaces(name));
    PlayerClass = GetPlayerClass(_class);
    if(ThisIsHack)
    {
        PlayerClass = ClassHack;
        SetName(SetSpaces(Name));
    }
    SetLevel(level);
    Exp = exp;
    IntStr = int_str;
    TalentPoints = talent_pts;
    SetMaxHealth(health);
    SetHealth(health);
    SetMaxPower(power);
    SetPower(power);
    SetWealth(wealth);
    SetAttack(attack);
    SetDefense(Defense);

    File >> x;
    while(x != 0)
    {
        File >> id;
        AddItem(GetItemFromDatabase(World, id));
        --x;
    }
    File >> x;
    while(x != 0)
    {
        File >> id;
        AddItem(GetItemFromDatabase(World, id), true);
        --x;
    }
    File >> x;
    while(x != 0)
    {
        File >> id;
        AddSpell(GetSpellFromDatabase(World, id));
        --x;
    }
    File >> x;
    while(x != 0)
    {
        File >> id;
        AddQuest(GetQuestFromDatabase(World, id));
        File >> id;
        auto itr = --Quests.end();
        itr->Objective.CurrentProgress = id;
        --x;
    }
    File >> x;
    while(x != 0)
    {
        File >> id;
        AddCompletedQuest(id);
        --x;
    }

    return PlayerClass;
}