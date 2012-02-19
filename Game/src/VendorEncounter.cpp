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
    ScreenTexture.Create(1024, 768);
}

void VendorEncounter::DrawItems(const Vendor& Vendor)
{
    int ItemX = 49, ItemY = 70;
    for(auto itr = player.GetItems().begin(); itr != player.GetItems().end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.SetPosition(ItemX, ItemY);
        ItemX += 81;
        if(ItemX == 324)
        {
            ItemY += 32;
            ItemX = 49;
        }
        Window.Draw(ItemSprite);
    }

    ItemX = 685; ItemY = 70;
    for(auto itr = Vendor.Items.begin(); itr != Vendor.Items.end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.SetPosition(ItemX, ItemY);
        ItemX += 81;
        if(ItemX == 1009)
        {
            ItemY += 32;
            ItemX = 685;
        }
        Window.Draw(ItemSprite);
    }
}

void VendorEncounter::BuyingItemsLoop(Vendor &Vendor)
{
    string Message = "How can I help you, " + player.GetName() + "?";
    unsigned i=0;
    for(int y=0; y<13; ++y)
    {
        for(int x=0; x<4; ++x)
        {
            if(i<Vendor.Items.size())
            {
                ItemGrid[y][x] = i;
            }
            else
            {
                ItemGrid[y][x] = -1;
            }
            ++i;
        }
    }
    int IterX = 0, IterY = 0;
    ArrowX = 636; ArrowY = 70;
    ArrowSprite.SetPosition(ArrowX, ArrowY);
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(IterY != 0)
                {
                    --IterY;
                    ArrowY -= 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(IterY != 12)
                {
                    ++IterY;
                    ArrowY += 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Right))
            {
                if(IterX != 3)
                {
                    ++IterX;
                    ArrowX += 81;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Left))
            {
                if(IterX != 0)
                {
                    --IterX;
                    ArrowX -= 81;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                if(player.GetWealth() < Vendor.Items[ItemGrid[IterY][IterX]].BuyPrice)
                {
                    Message = "You cannot afford that item!";
                    continue;
                }
                player.SetWealth(player.GetWealth() - Vendor.Items[ItemGrid[IterY][IterX]].BuyPrice);
                player.AddItem(Vendor.Items[ItemGrid[IterY][IterX]]);
                //Vendor.Items.erase(Vendor.Items.begin() + ItemGrid[IterY][IterX]);
                Message = "It's been pleasure trading with you, " + player.GetName();
                MoneyText.SetString(IntToString(player.GetWealth()));
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.Clear();
        Window.Draw(GUISprite);
        Window.Draw(ArrowSprite);
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        DrawMessage(Message);
        DrawItems(Vendor);
        Window.Draw(MoneySprite);
        Window.Draw(MoneyText);
        Window.Display();
    }
}

void VendorEncounter::SellingItemsLoop(Vendor &Vendor)
{
    string Message = "How can I help you, " + player.GetName() + "?";
    unsigned i=0;
    for(int y=0; y<13; ++y)
    {
        for(int x=0; x<4; ++x)
        {
            if(i<player.GetItems().size())
            {
                ItemGrid[y][x] = i;
            }
            else
            {
                ItemGrid[y][x] = -1;
            }
            ++i;
        }
    }
    int IterX = 0, IterY = 0;
    ArrowX = 0; ArrowY = 70;
    ArrowSprite.SetPosition(ArrowX, ArrowY);
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(IterY != 0)
                {
                    --IterY;
                    ArrowY -= 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(IterY != 12)
                {
                    ++IterY;
                    ArrowY += 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Right))
            {
                if(IterX != 3)
                {
                    ++IterX;
                    ArrowX += 81;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Left))
            {
                if(IterX != 0)
                {
                    --IterX;
                    ArrowX -= 81;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(player.GetItems()[ItemGrid[IterY][IterX]].Type)
                {
                case ITEM_QUEST:
                    Message = "I don't want that item.";
                    break;
                default:
                    player.SetWealth(player.GetWealth() + player.GetItems()[ItemGrid[IterY][IterX]].SellPrice);
                    //Vendor.Items.push_back(player.GetItems()[ItemGrid[IterY][IterX]]);
                    player.RemoveItem(ItemGrid[IterY][IterX]);
                    MoneyText.SetString(IntToString(player.GetWealth()));
                    break;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.Clear();
        Window.Draw(GUISprite);
        Window.Draw(ArrowSprite);
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        DrawItems(Vendor);
        DrawMessage(Message);
        Window.Draw(MoneySprite);
        Window.Draw(MoneyText);
        Window.Display();
    }
}

void VendorEncounter::DrawTexture()
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
    YourItems.SetPosition(100.0f, 0.0f);
    VendorItems.SetPosition(750.0f, 0.0f);

    ScreenTexture.Draw(BuyItem);
    ScreenTexture.Draw(Return);
    ScreenTexture.Draw(SellItem);
    ScreenTexture.Draw(YourItems);
    ScreenTexture.Draw(VendorItems);
    ScreenTexture.Display();
}

void VendorEncounter::DrawMessage(string Message)
{
    sf::Text Text(Message, Font);
    Text.SetPosition(247.0f, 640.0f);
    Text.SetStyle(sf::Text::Bold);
    Text.SetColor(sf::Color::Black);
    Window.Draw(Text);
}

Vendor VendorEncounter::MainLoop(Vendor Vendor)
{
    DrawTexture();
    MoneyText.SetString(IntToString(player.GetWealth()));
    MoneyText.SetStyle(sf::Text::Bold);
    MoneyText.SetColor(sf::Color::Black);
    MoneyText.SetPosition(410.0f, 20.0f);
    sf::Texture ArrowTexture, GUITexture, MoneyTexture;
    MoneyTexture.LoadFromFile("Items/Money.png");
    MoneySprite.SetTexture(MoneyTexture);
    MoneySprite.SetPosition(380.0f, 20.0f);
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
                    BuyingItemsLoop(Vendor);
                    break;
                case 1:
                    SellingItemsLoop(Vendor);
                    break;
                case 2:
                    return Vendor;
                }
                Command = 0;
                ArrowX = 405.0f;
                ArrowY = 370.0f;
                ArrowSprite.SetPosition(ArrowX, ArrowY);
            }
        }
        Window.Clear();
        Window.Draw(GUISprite);
        DrawItems(Vendor);
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        Window.Draw(ArrowSprite);
        DrawMessage("How can I help you, " + player.GetName() + "?");
        Window.Draw(MoneySprite);
        Window.Draw(MoneyText);
        Window.Display();
    }
    return Vendor;
}