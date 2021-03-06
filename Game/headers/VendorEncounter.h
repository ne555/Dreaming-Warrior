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
#ifndef VENDOR_ENCOUNTER_H
#define VENDOR_ENCOUNTER_H

#include "vendor.h"
#include "player.h"

class VendorEncounter
{
    sf::RenderWindow &Window;
    sf::Event Event;
    sf::Sprite ArrowSprite;
    sf::Sprite GUISprite;
    sf::Texture ScreenTexture;
    sf::Sprite MoneySprite;
    sf::Text MoneyText;
    sf::Text ItemName;
    sf::Sprite ItemSprite;

    Player &player;
    Vendor &vendor;

    sf::Font Font;

    sf::Text BuyItem, SellItem, YourItems, VendorItems, Return;

    float ArrowX;
    float ArrowY;

    int ItemGrid[13][4];

    void DrawTexture();
    void DrawMessage(string Message);
    void DrawItems();
    void SellingItemsLoop();
    void BuyingItemsLoop();

public:
    VendorEncounter(Player &Player, sf::RenderWindow &Window, Vendor &vendor);
    void MainLoop();
};

#endif