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
#include "characterscreen.h"
#include "QuestScreen.h"
#include "player.h"

/*
Ostavi mjesta meðu itemima za strelicu koja je 32x32
*/

CharacterScreen::CharacterScreen(Player &player, sf::RenderWindow &Window)
    : Window(Window), player(player)
{
    ScreenTexture.Create(1024, 768);
    int i=0;
    for(int y=0; y<5; ++y)
    {
        for(int x=0; x<6; ++x)
        {
            if(i < player.GetItems().size())
                ItemGrid[y][x] = i;
            else
                ItemGrid[y][x] = -1;
        }
    }
}

void CharacterScreen::ItemsLoop()
{
    float ArrowX = 0, ArrowY = 571;
    ArrowSprite.SetPosition(ArrowX, ArrowY);
    int IterX = 0, IterY = 0;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(IterY != 0 && (ItemGrid[IterY-1][IterX] != -1))
                {
                    IterY -= 1;
                    ArrowY -= 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(IterY != 4 && (ItemGrid[IterY+1][IterX] != -1))
                {
                    IterY += 1;
                    ArrowY += 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Right))
            {
                if(IterX != 5 && (ItemGrid[IterY][IterX+1] != -1))
                {
                    IterX += 1;
                    ArrowX += 79;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Left))
            {
                if(IterX != 0 && (ItemGrid[IterY][IterX-1] != -1))
                {
                    IterX -= 1;
                    ArrowX -= 79;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(player.GetItems()[ItemGrid[IterY][IterX]].Type)
                {
                case ITEM_QUEST:
                case ITEM_POWER_POTION:
                case ITEM_HEALTH_POTION:
                    break;
                default:
                    player.EquipItem(player.GetItems()[ItemGrid[IterY][IterX]]);
                    player.RemoveItem(ItemGrid[IterY][IterX]);
                    int i=0;
                    for(int y=0; y<5; ++y)
                    {
                        for(int x=0; x<6; ++x)
                        {
                            if(i < player.GetItems().size()-1)
                                ItemGrid[y][x] = i;
                            else
                                ItemGrid[y][x] = -1;
                        }
                    }
                    break;
                }
            }
            //else if D drop item?
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        //drawat statse trenutnog itema :P
        //drawat grid kao u map editoru
        Window.Clear();
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        DrawItems();
        Window.Draw(ArrowSprite);
        Window.Display();
    }
}

void CharacterScreen::SpellsLoop()
{
    if(player.GetSpells().empty())
        return;
    int Iterator = 0;
    float ArrowY = 50.0f;
    ArrowSprite.SetPosition(760.0f, ArrowY);
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(Iterator != 0)
                {
                    --Iterator;
                    ArrowY -= 35;
                    ArrowSprite.SetPosition(760.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Iterator != player.GetSpells().size()-1)
                {
                    ++Iterator;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(760.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.Clear();
        //TODO draw spell detalje ovisno o iteratoru
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        Window.Draw(ArrowSprite);
        Window.Display();
    }
}

void CharacterScreen::StatsLoop()
{
    int Iterator = 0;
    float ArrowY = 90.0f;
    ArrowSprite.SetPosition(165.0f, ArrowY);
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(Iterator != 0)
                {
                    --Iterator;
                    ArrowY -= 35;
                    ArrowSprite.SetPosition(165.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Iterator != 3)
                {
                    ++Iterator;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(165.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                //todo [PH]
                switch(Iterator)
                {
                case 0:
                    player.SetMaxHealth(player.GetMaxHealth() + 10);
                    break;
                case 1:
                    player.SetMaxPower(player.GetMaxPower() + 10);
                    break;
                case 2:
                    player.SetAttackPower(player.GetAttackPower() + 5);
                    break;
                case 3:
                    player.SetArmor(player.GetArmor() + 5);
                    break;
                }
                player.UseTalentPoint();
                DrawTexture(); //TODO odvojiti stats textove u vise funkcija radi performansa
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.Clear();
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        Window.Draw(ArrowSprite);
        Window.Display();
    }
}

void CharacterScreen::DrawItems()
{
    float ItemX = 47, ItemY = 571;
    for(auto itr = player.GetItems().begin(); itr != player.GetItems().end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.SetPosition(ItemX, ItemY);
        ItemX +=79;
        if(ItemX == 474)
        {
            ItemY -= 32;
            ItemX = 79;
        }
        Window.Draw(ItemSprite);
    }
}

void CharacterScreen::DrawTexture()
{
    //Graphics
    sf::Texture PlayerTexture, BackgroundTexture;
    switch(player.GetClass())
    {
    case CLASS_WARRIOR:
        PlayerTexture.LoadFromFile("Graphics/Warrior.png");
        break;
    case CLASS_MAGE:
        PlayerTexture.LoadFromFile("Graphics/Mage.png");
        break;
    }
    BackgroundTexture.LoadFromFile("Graphics/CharacterScreen.png");
    PlayerSprite.SetTexture(PlayerTexture);
    BackgroundSprite.SetTexture(BackgroundTexture);

    //Texts
    sf::Text Items("Items"), Spells("Spells"), Stats("Stats"), Quests("Quests"), Exit("Exit"),
        PointsText("Attribute points left: " + IntToString(player.GetTalentPoints())),
        HealthText("Health: " + IntToString(player.GetHealth()) + "/" + IntToString(player.GetMaxHealth())),
        PowerText,
        AttackText("Attack: " + IntToString(player.GetAttackPower())), 
        DefenseText("Armor: " + IntToString(player.GetArmor()));

    float SpellTextY = 50;
    for(auto itr = player.GetSpells().begin(); itr != player.GetSpells().end(); ++itr)
    {
        sf::Text SpellText(itr->Name);
        SpellText.SetPosition(800, SpellTextY);
        SpellTextY += 35;
        ScreenTexture.Draw(SpellText);
    }

    if(player.GetClass() == CLASS_WARRIOR)
        PowerText.SetString("Stamina: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));
    else
        PowerText.SetString("Mana: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));

    PointsText.SetPosition(200, 55);
    HealthText.SetPosition(200, 90);
    PowerText.SetPosition(200, 125);
    AttackText.SetPosition(200, 160);
    DefenseText.SetPosition(200, 195);
    Items.SetPosition(850.0f, 550.0f);
    Spells.SetPosition(850.0f, 585.0f);
    Stats.SetPosition(850.0f, 625.0f);
    Quests.SetPosition(850.0f, 660.0f);
    Exit.SetPosition(850.0f, 695.0f);

    //ScreenTexture.Draw(BackgroundSprite);
    ScreenTexture.Draw(PlayerSprite);
    ScreenTexture.Draw(PointsText);
    ScreenTexture.Draw(HealthText);
    ScreenTexture.Draw(PowerText);
    ScreenTexture.Draw(AttackText);
    ScreenTexture.Draw(DefenseText);
    ScreenTexture.Draw(Spells);
    ScreenTexture.Draw(Stats);
    ScreenTexture.Draw(Items);
    ScreenTexture.Draw(Quests);
    ScreenTexture.Draw(Exit);
    ScreenTexture.Display();
}

void CharacterScreen::MainLoop()
{
    sf::Texture ArrowTexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
    ArrowSprite.SetTexture(ArrowTexture);
    ArrowSprite.SetPosition(800.0f, 550.0f);
    DrawTexture();
    int Command = 1;
    float ArrowY = 550.0f;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(Command != 1)
                {
                    --Command;
                    ArrowY -= 35;
                    ArrowSprite.SetPosition(800.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Command != 5)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(800.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(Command)
                {
                case 1:
                    ItemsLoop();
                    break;
                case 2:
                    SpellsLoop();
                    break;
                case 3:
                    if(player.GetTalentPoints() > 0)
                        StatsLoop();
                    break;
                case 4:
                    {
                        QuestScreen QuestScreen(player, Window);
                        QuestScreen.MainLoop();
                    }
                    break;
                case 5:
                    return;
                }
                ArrowSprite.SetPosition(800.0f, ArrowY);
            }
        }
        Window.Clear();
        //Window.Draw(BackgroundSprite);
    /*for(int i=0; i<player.GetEquipedItems().size(); ++i)
    {
        sf::Sprite ItemSprite(player.GetItems()[i].ItemTexture);
        switch(player.GetItems()[i].Type)
        {
        case ITEM_HEAD:
            //ItemSprite.SetPosition();
            break;
        case ITEM_CHEST:
            //ItemSprite.SetPosition();
            break;
        case ITEM_HANDS:
            //ItemSprite.SetPosition();
            break;
        case ITEM_LEGS:
            //ItemSprite.SetPosition();
            break;
        case ITEM_FOOT:
            //ItemSprite.SetPosition();
            break;
        case ITEM_WEAPON:
            //ItemSprite.SetPosition();
            break;
        }
        Window.Draw(ItemSprite);
    }*/
        //TODO: i itemi iz torbice
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        Window.Draw(ArrowSprite);
        DrawItems();
        Window.Display();
    }
}