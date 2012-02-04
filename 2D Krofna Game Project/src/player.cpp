#include "player.h"

Player::Player()
{
}

Player::~Player()
{
    while(!Items.empty()) delete Items.back(), Items.pop_back();
    while(!EquipedItems.empty()) delete EquipedItems.back(), EquipedItems.pop_back();
}

void Player::LoadFromFile(std::string LoadFileName = "")
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