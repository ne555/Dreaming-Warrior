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
    : player(player), Window(Window), ArrowX(405), ArrowY(370)
{
}

Vendor VendorEncounter::MainLoop(Vendor Vendor)
{
    Font.LoadFromFile("Graphics/papyrus.ttf");
    sf::Text 
        BuyItem("Buy Item", Font), SellItem("Sell Item", Font), 
        YourItems("Your items: ", Font), VendorItems("Vendors items: ", Font),
        Return("Back to Game", Font);

    BuyItem.SetColor(sf::Color::Black);
    SellItem.SetColor(sf::Color::Black);
    YourItems.SetColor(sf::Color::Black);
    VendorItems.SetColor(sf::Color::Black);
    Return.SetColor(sf::Color::Black);

    BuyItem.SetStyle(sf::Text::Bold);
    SellItem.SetStyle(sf::Text::Bold);
    YourItems.SetStyle(sf::Text::Bold);
    VendorItems.SetStyle(sf::Text::Bold);
    Return.SetStyle(sf::Text::Bold);

    BuyItem.SetPosition(450.0f, 370.0f);
    SellItem.SetPosition(450.0f, 405.0f);
    Return.SetPosition(450.0f, 440.0f);
    YourItems.SetPosition(100.0f, 80.0f);
    VendorItems.SetPosition(750.0f, 80.0f);

    sf::Texture ArrowTexture, GUITexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow2.png");
    GUITexture.LoadFromFile("Graphics/VendorScreen.png");
    ArrowSprite.SetTexture(ArrowTexture);
    ArrowSprite.SetPosition(ArrowX, ArrowY);
    GUISprite.SetTexture(GUITexture);
    
    int Command = 0;

    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(Command != 0)
                {
                    --Command;
                    ArrowY -= 35;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Command != 2)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(Command)
                {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    return Vendor;
                }
            }
        }
        Window.Clear();
        Window.Draw(GUISprite);
        Window.Draw(BuyItem);
        Window.Draw(Return);
        Window.Draw(SellItem);
        Window.Draw(YourItems);
        Window.Draw(VendorItems);
        Window.Draw(ArrowSprite);
        Window.Display();
    }
    return Vendor;
}