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
#include "player.h"
#include "database.h"

void Player::LoadFromFile(string World)
{
    std::ifstream File(World + "/Player.txt");
    int x, y, level, exp, int_str, health, power, attack, armor, id;
    bool _class;
    string name;
    File >> x >> y >> name >> _class >> level >> exp >> int_str >> health >> power >> attack >> armor;
    SetX(x);
    SetY(y);
    SetName(name);
    if(_class)
        PlayerClass = CLASS_MAGE;
    else
        PlayerClass = CLASS_WARRIOR;
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
    File >> y;
    while(y != 0)
    {
        File >> id;
        AddSpell(GetSpellFromDatabase(World, id));
        --x;
    }
}