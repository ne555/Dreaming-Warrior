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

Class Player::LoadFromFile(string World, Class ClassHack, bool ThisIsHack)
{
    std::ifstream File(World + "/Player.txt");
    int x, y, level, exp, int_str, health, power, attack, armor, id, _class;
    string name, map;
    File >> map >> x >> y >> name >> _class >> level >> exp >> int_str >> health >> power >> attack >> armor;
    Map = map;
    SetX(x);
    SetY(y);
    SetName(name);
    PlayerClass = GetPlayerClass(_class);
    if(ThisIsHack)
        PlayerClass = ClassHack;
    SetLevel(level);
    Exp = exp;
    IntStr = int_str;
    SetHealth(health);
    SetMaxHealth(health);
    SetPower(power);
    SetMaxPower(power);
    SetAttackPower(attack);
    SetArmor(armor);

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
        --x;
    }
    File >> x;
    while(x != 0)
    {
        File >> id;
        AddFinishedQuest(id);
        --x;
    }

    return PlayerClass;
}