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

VendorEncounter::VendorEncounter(Player &player, sf::RenderWindow &Window, Vendor &vendor)
    : player(player), vendor(vendor), Window(Window), ArrowX(405), ArrowY(370)
{
    ItemName.setColor(sf::Color::Black);
    BuyItem.setColor(sf::Color::Black);
    SellItem.setColor(sf::Color::Black);
    YourItems.setColor(sf::Color::Black);
    VendorItems.setColor(sf::Color::Black);
    Return.setColor(sf::Color::Black);

    ItemName.setStyle(sf::Text::Bold);
    BuyItem.setStyle(sf::Text::Bold);
    SellItem.setStyle(sf::Text::Bold);
    YourItems.setStyle(sf::Text::Bold);
    VendorItems.setStyle(sf::Text::Bold);
    Return.setStyle(sf::Text::Bold);

    ItemName.setPosition(390.0f, 70.0f);
    BuyItem.setPosition(450.0f, 370.0f);
    SellItem.setPosition(450.0f, 405.0f);
    Return.setPosition(450.0f, 440.0f);
    YourItems.setPosition(100.0f, 0.0f);
    VendorItems.setPosition(750.0f, 0.0f);

    ItemName.setFont(Font);
    BuyItem.setFont(Font);
    SellItem.setFont(Font);
    YourItems.setFont(Font);
    VendorItems.setFont(Font);
    Return.setFont(Font);

    ItemName.setCharacterSize(20);
    ItemSprite.setPosition(360.0f, 70.0f);
    ScreenTexture.create(1024, 768);
}

void VendorEncounter::DrawItems()
{
    int ItemX = 49, ItemY = 70;
    for(auto itr = player.GetItems().begin(); itr != player.GetItems().end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.setPosition((float)ItemX, (float)ItemY);
        ItemX += 81;
        if(ItemX == 373)
        {
            ItemY += 32;
            ItemX = 49;
        }
        Window.draw(ItemSprite);
    }

    ItemX = 685; ItemY = 70;
    for(auto itr = vendor.Items.begin(); itr != vendor.Items.end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.setPosition((float)ItemX, (float)ItemY);
        ItemX += 81;
        if(ItemX == 1009)
        {
            ItemY += 32;
            ItemX = 685;
        }
        Window.draw(ItemSprite);
    }
}

void VendorEncounter::BuyingItemsLoop()
{
    string Message = "How can I help you, " + player.GetName() + "?";
    unsigned i=0;
    for(int y=0; y<13; ++y)
    {
        for(int x=0; x<4; ++x)
        {
            if(i < vendor.Items.size())
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
    ArrowSprite.setPosition(ArrowX, ArrowY);
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(IterY != 0)
                {
                    --IterY;
                    ArrowY -= 32;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(IterY != 12)
                {
                    ++IterY;
                    ArrowY += 32;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
            {
                if(IterX != 3)
                {
                    ++IterX;
                    ArrowX += 81;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
            {
                if(IterX != 0)
                {
                    --IterX;
                    ArrowX -= 81;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                if(player.GetWealth() < vendor.Items[ItemGrid[IterY][IterX]].BuyPrice)
                {
                    Message = "You cannot afford that item!";
                    continue;
                }
                if(player.GetItems().size() == MAX_ITEMS)
                {
                    Message = "You cannot carry any more items";
                    continue;
                }
                player.SetWealth(player.GetWealth() - vendor.Items[ItemGrid[IterY][IterX]].BuyPrice);
                player.AddItem(vendor.Items[ItemGrid[IterY][IterX]]);
                Message = "It's been pleasure trading with you, " + player.GetName();
                MoneyText.setString(IntToString(player.GetWealth()));
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.clear();
        Window.draw(GUISprite);
        Window.draw(ArrowSprite);
        Window.draw(sf::Sprite(ScreenTexture));
        DrawMessage(Message);
        DrawItems();
        Window.draw(MoneySprite);
        Window.draw(MoneyText);
        if(ItemGrid[IterY][IterX] != -1)
        {
            ItemSprite.setTexture(vendor.Items[ItemGrid[IterY][IterX]].ItemTexture);
            switch(vendor.Items[ItemGrid[IterY][IterX]].Type) //PH
            {
            case ITEM_FOOD:
                ItemName.setString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_MANA_FOOD:
                ItemName.setString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_POWER_POTION:
                ItemName.setString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_HEALTH_POTION:
                ItemName.setString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            }
            Window.draw(ItemSprite);
            Window.draw(ItemName);
        }
        Window.display();
    }
}

void VendorEncounter::SellingItemsLoop()
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
    ArrowSprite.setPosition(ArrowX, ArrowY);
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(IterY != 0)
                {
                    --IterY;
                    ArrowY -= 32;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(IterY != 12)
                {
                    ++IterY;
                    ArrowY += 32;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
            {
                if(IterX != 3)
                {
                    ++IterX;
                    ArrowX += 81;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
            {
                if(IterX != 0)
                {
                    --IterX;
                    ArrowX -= 81;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                switch(player.GetItems()[ItemGrid[IterY][IterX]].Type)
                {
                case ITEM_QUEST:
                    Message = "I don't want that item.";
                    break;
                default:
                    player.SetWealth(player.GetWealth() + player.GetItems()[ItemGrid[IterY][IterX]].SellPrice);
                    player.RemoveItem(ItemGrid[IterY][IterX]);
                    MoneyText.setString(IntToString(player.GetWealth()));
                    break;
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.clear();
        Window.draw(GUISprite);
        Window.draw(ArrowSprite);
        Window.draw(sf::Sprite(ScreenTexture));
        DrawItems();
        DrawMessage(Message);
        Window.draw(MoneySprite);
        Window.draw(MoneyText);
        if(ItemGrid[IterY][IterX] != -1)
        {
            ItemSprite.setTexture(player.GetItems()[ItemGrid[IterY][IterX]].ItemTexture);
            switch(player.GetItems()[ItemGrid[IterY][IterX]].Type) //PH
            {
            case ITEM_FOOD:
                ItemName.setString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_POWER_POTION:
                ItemName.setString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_HEALTH_POTION:
                ItemName.setString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            }
            Window.draw(ItemName);
            Window.draw(ItemSprite);
        }
        Window.display();
    }
}

void VendorEncounter::DrawTexture()
{
    sf::RenderTexture ScreenTexture;
    ScreenTexture.create(1024, 768);

    ScreenTexture.draw(BuyItem);
    ScreenTexture.draw(Return);
    ScreenTexture.draw(SellItem);
    ScreenTexture.draw(YourItems);
    ScreenTexture.draw(VendorItems);
    ScreenTexture.display();
    this->ScreenTexture = ScreenTexture.getTexture();
}

void VendorEncounter::DrawMessage(string Message)
{
    sf::Text Text(Message, Font);
    Text.setPosition(247.0f, 640.0f);
    Text.setStyle(sf::Text::Bold);
    Text.setColor(sf::Color::Black);
    Window.draw(Text);
}

void VendorEncounter::MainLoop()
{
    Font.loadFromFile("Graphics/papyrus.ttf");
    BuyItem.setString("Buy Item");
    SellItem.setString("Sell Item");
    YourItems.setString("Your items: ");
    VendorItems.setString("Vendors items: ");
    Return.setString("Back to Game");
    DrawTexture();
    MoneyText.setString(IntToString(player.GetWealth()));
    MoneyText.setStyle(sf::Text::Bold);
    MoneyText.setColor(sf::Color::Black);
    MoneyText.setPosition(410.0f, 20.0f);
    sf::Texture ArrowTexture, GUITexture, MoneyTexture;
    MoneyTexture.loadFromFile("Items/Money.png");
    MoneyText.setFont(Font);
    MoneySprite.setTexture(MoneyTexture);
    MoneySprite.setPosition(380.0f, 20.0f);
    ArrowTexture.loadFromFile("Graphics/Arrow2.png");
    GUITexture.loadFromFile("Graphics/VendorScreen.png");
    ArrowSprite.setTexture(ArrowTexture);
    ArrowSprite.setPosition(ArrowX, ArrowY);
    GUISprite.setTexture(GUITexture);
    int Command = 0;

    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(Command != 0)
                {
                    --Command;
                    ArrowY -= 35;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(Command != 2)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                switch(Command)
                {
                case 0:
                    BuyingItemsLoop();
                    break;
                case 1:
                    SellingItemsLoop();
                    break;
                case 2:
                    return;
                }
                Command = 0;
                ArrowX = 405.0f;
                ArrowY = 370.0f;
                ArrowSprite.setPosition(ArrowX, ArrowY);
            }
        }
        Window.clear();
        Window.draw(GUISprite);
        DrawItems();
        Window.draw(sf::Sprite(ScreenTexture));
        Window.draw(ArrowSprite);
        DrawMessage("How can I help you, " + player.GetName() + "?");
        Window.draw(MoneySprite);
        Window.draw(MoneyText);
        Window.display();
    }
}