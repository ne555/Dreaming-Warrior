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
#include "VendorEncounter.h"

VendorEncounter::VendorEncounter(Player &player, sf::RenderWindow &Window)
    : player(player), Window(Window)
{
}

sf::Texture VendorEncounter::DrawInterface()
{
    sf::RenderTexture ScreenTexture;
    sf::Texture PlayerTexture, VendorTexture;
    sf::Text BuyItem("Buy Item", Font), SellItem("Sell Item", Font);
    switch(player.GetClass())
    {
    case CLASS_WARRIOR:
        PlayerTexture.LoadFromFile("Graphics/Warrior.png");
        break;
    case CLASS_MAGE:
        PlayerTexture.LoadFromFile("Graphics/Mage.png");
        break;
    }
}

Vendor VendorEncounter::MainLoop(Vendor Vendor)
{
    sf::Texture ArrowTexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
    Font.LoadFromFile("Graphics/papyrus.ttf");
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
            }
        }
        Window.Clear();
        Window.Display();
    }
    return Vendor;
}