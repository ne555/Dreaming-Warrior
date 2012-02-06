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

Player::Player()
{
}

Player::~Player()
{
    while(!Items.empty()) delete Items.back(), Items.pop_back();
    while(!EquipedItems.empty()) delete EquipedItems.back(), EquipedItems.pop_back();
}

void Player::LoadFromFile(string LoadFileName = "")
{
    std::ifstream File(LoadFileName);
    //bla bla PH
    if(LoadFileName == "")
    {
        SetX(32);
        SetY(32);
        SetName("Pero");
        PlayerClass = CLASS_WARRIOR;
        SetLevel(1);
        Exp = 0;
        IntStr = 1;
        SetHealth(2000);
        SetMaxHealth(20);
        SetPower(20);
        SetMaxPower(20);
        SetAttackPower(10);
        SetArmor(5);
    }
}