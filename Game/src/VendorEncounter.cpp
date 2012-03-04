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
    ItemName.SetColor(sf::Color::Black);
    BuyItem.SetColor(sf::Color::Black);
    SellItem.SetColor(sf::Color::Black);
    YourItems.SetColor(sf::Color::Black);
    VendorItems.SetColor(sf::Color::Black);
    Return.SetColor(sf::Color::Black);

    ItemName.SetStyle(sf::Text::Bold);
    BuyItem.SetStyle(sf::Text::Bold);
    SellItem.SetStyle(sf::Text::Bold);
    YourItems.SetStyle(sf::Text::Bold);
    VendorItems.SetStyle(sf::Text::Bold);
    Return.SetStyle(sf::Text::Bold);

    ItemName.SetPosition(390.0f, 70.0f);
    BuyItem.SetPosition(450.0f, 370.0f);
    SellItem.SetPosition(450.0f, 405.0f);
    Return.SetPosition(450.0f, 440.0f);
    YourItems.SetPosition(100.0f, 0.0f);
    VendorItems.SetPosition(750.0f, 0.0f);

    ItemName.SetFont(Font);
    BuyItem.SetFont(Font);
    SellItem.SetFont(Font);
    YourItems.SetFont(Font);
    VendorItems.SetFont(Font);
    Return.SetFont(Font);

    ItemName.SetCharacterSize(20);
    ItemSprite.SetPosition(360.0f, 70.0f);
    ScreenTexture.Create(1024, 768);
}

void VendorEncounter::DrawItems()
{
    int ItemX = 49, ItemY = 70;
    for(auto itr = player.GetItems().begin(); itr != player.GetItems().end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.SetPosition((float)ItemX, (float)ItemY);
        ItemX += 81;
        if(ItemX == 373)
        {
            ItemY += 32;
            ItemX = 49;
        }
        Window.Draw(ItemSprite);
    }

    ItemX = 685; ItemY = 70;
    for(auto itr = vendor.Items.begin(); itr != vendor.Items.end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.SetPosition((float)ItemX, (float)ItemY);
        ItemX += 81;
        if(ItemX == 1009)
        {
            ItemY += 32;
            ItemX = 685;
        }
        Window.Draw(ItemSprite);
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
        Window.Draw(sf::Sprite(ScreenTexture));
        DrawMessage(Message);
        DrawItems();
        Window.Draw(MoneySprite);
        Window.Draw(MoneyText);
        if(ItemGrid[IterY][IterX] != -1)
        {
            ItemSprite.SetTexture(vendor.Items[ItemGrid[IterY][IterX]].ItemTexture);
            switch(vendor.Items[ItemGrid[IterY][IterX]].Type) //PH
            {
            case ITEM_FOOD:
                ItemName.SetString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_MANA_FOOD:
                ItemName.SetString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_POWER_POTION:
                ItemName.SetString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_HEALTH_POTION:
                ItemName.SetString
                    (vendor.Items[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(vendor.Items[ItemGrid[IterY][IterX]].SellPrice));
                break;
            }
            Window.Draw(ItemSprite);
            Window.Draw(ItemName);
        }
        Window.Display();
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
        Window.Draw(sf::Sprite(ScreenTexture));
        DrawItems();
        DrawMessage(Message);
        Window.Draw(MoneySprite);
        Window.Draw(MoneyText);
        if(ItemGrid[IterY][IterX] != -1)
        {
            ItemSprite.SetTexture(player.GetItems()[ItemGrid[IterY][IterX]].ItemTexture);
            switch(player.GetItems()[ItemGrid[IterY][IterX]].Type) //PH
            {
            case ITEM_FOOD:
                ItemName.SetString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_POWER_POTION:
                ItemName.SetString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_HEALTH_POTION:
                ItemName.SetString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            }
            Window.Draw(ItemName);
            Window.Draw(ItemSprite);
        }
        Window.Display();
    }
}

void VendorEncounter::DrawTexture()
{
    sf::RenderTexture ScreenTexture;
    ScreenTexture.Create(1024, 768);

    ScreenTexture.Draw(BuyItem);
    ScreenTexture.Draw(Return);
    ScreenTexture.Draw(SellItem);
    ScreenTexture.Draw(YourItems);
    ScreenTexture.Draw(VendorItems);
    ScreenTexture.Display();
    this->ScreenTexture = ScreenTexture.GetTexture();
}

void VendorEncounter::DrawMessage(string Message)
{
    sf::Text Text(Message, Font);
    Text.SetPosition(247.0f, 640.0f);
    Text.SetStyle(sf::Text::Bold);
    Text.SetColor(sf::Color::Black);
    Window.Draw(Text);
}

void VendorEncounter::MainLoop()
{
    Font.LoadFromFile("Graphics/papyrus.ttf");
    BuyItem.SetString("Buy Item");
    SellItem.SetString("Sell Item");
    YourItems.SetString("Your items: ");
    VendorItems.SetString("Vendors items: ");
    Return.SetString("Back to Game");
    DrawTexture();
    MoneyText.SetString(IntToString(player.GetWealth()));
    MoneyText.SetStyle(sf::Text::Bold);
    MoneyText.SetColor(sf::Color::Black);
    MoneyText.SetPosition(410.0f, 20.0f);
    sf::Texture ArrowTexture, GUITexture, MoneyTexture;
    MoneyTexture.LoadFromFile("Items/Money.png");
    MoneyText.SetFont(Font);
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
                ArrowSprite.SetPosition(ArrowX, ArrowY);
            }
        }
        Window.Clear();
        Window.Draw(GUISprite);
        DrawItems();
        Window.Draw(sf::Sprite(ScreenTexture));
        Window.Draw(ArrowSprite);
        DrawMessage("How can I help you, " + player.GetName() + "?");
        Window.Draw(MoneySprite);
        Window.Draw(MoneyText);
        Window.Display();
    }
}