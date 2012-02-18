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

CharacterScreen::CharacterScreen(Player &player, sf::RenderWindow &Window)
    : Window(Window), player(player)
{
    ScreenTexture.Create(1024, 768);
}

void CharacterScreen::ItemsLoop()
{
    unsigned i=0;
    for(int y=0; y<6; ++y)
    {
        for(int x=0; x<6; ++x)
        {
            if(i < player.GetItems().size())
                ItemGrid[y][x] = i;
            else
                ItemGrid[y][x] = -1;
            ++i;
        }
    }
    float ArrowX = 0, ArrowY = 571;
    ArrowSprite.SetPosition(ArrowX, ArrowY);
    int IterX = 0, IterY = 0;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(IterY != 0)
                {
                    IterY -= 1;
                    ArrowY -= 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(IterY != 5)
                {
                    IterY += 1;
                    ArrowY += 32;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Right))
            {
                if(IterX != 5)
                {
                    IterX += 1;
                    ArrowX += 79;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Left))
            {
                if(IterX != 0)
                {
                    IterX -= 1;
                    ArrowX -= 79;
                    ArrowSprite.SetPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                if(ItemGrid[IterY][IterX] == -1)
                    continue;
                switch(player.GetItems()[ItemGrid[IterY][IterX]].Type)
                {
                case ITEM_QUEST:
                case ITEM_POWER_POTION:
                case ITEM_HEALTH_POTION:
                    break;
                default:
                    player.EquipItem(player.GetItems()[ItemGrid[IterY][IterX]]);
                    player.RemoveItem(ItemGrid[IterY][IterX]);
                    unsigned i=0;
                    for(int y=0; y<6; ++y)
                    {
                        for(int x=0; x<6; ++x)
                        {
                            if(i < player.GetItems().size()-1)
                                ItemGrid[y][x] = i;
                            else
                                ItemGrid[y][x] = -1;
                            ++i;
                        }
                    }
                    break;
                }
                IterY = IterX = 0;
                ArrowX = 0; ArrowY = 571;
            }
            //else if D drop item?
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::D))
            {
                if(ItemGrid[IterY][IterX] == -1)
                    continue;
                player.RemoveItem(ItemGrid[IterY][IterX]);
                unsigned i=0;
                for(int y=0; y<6; ++y)
                {
                    for(int x=0; x<6; ++x)
                    {
                        if(i < player.GetItems().size()-1)
                            ItemGrid[y][x] = i;
                        else
                            ItemGrid[y][x] = -1;
                        ++i;
                    }
                }
                IterY = IterX = 0;
                ArrowX = 0; ArrowY = 571;
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        //drawat statse trenutnog itema :P
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
                    player.SetAttack(player.GetAttack() + 5);
                    break;
                case 3:
                    player.SetDefense(player.GetDefense() + 5);
                    break;
                case 4:
                    break;//todo
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
        DrawItems();
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
    for(int a=47; a<474; a+=79)
    {
        sf::VertexArray Line(sf::Lines, 2);
        Line[0].Position = sf::Vector2f(a, 571.0f);
        Line[0].Color = sf::Color(0, 0, 0);
        Line[1].Position = sf::Vector2f(a, 763.0f);
        Line[1].Color = sf::Color(0, 0, 0);
        Window.Draw(Line);
    }
    for(int a=79; a<503; a+=79)
    {
        sf::VertexArray Line(sf::Lines, 2);
        Line[0].Position = sf::Vector2f(a, 571.0f);
        Line[0].Color = sf::Color(0, 0, 0);
        Line[1].Position = sf::Vector2f(a, 763.0f);
        Line[1].Color = sf::Color(0, 0, 0);
        Window.Draw(Line);
    }
    for(int a=571; a<768; a+=32)
    {
        sf::VertexArray Line(sf::Lines, 2);
        Line[0].Position = sf::Vector2f(0.0f, a);
        Line[0].Color = sf::Color(0, 0, 0);
        Line[1].Position = sf::Vector2f(474.0f, a);
        Line[1].Color = sf::Color(0, 0, 0);
        Window.Draw(Line);
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
    BackgroundTexture.LoadFromFile("Graphics/CharacterScreen.jpg");
    PlayerSprite.SetTexture(PlayerTexture);
    BackgroundSprite.SetTexture(BackgroundTexture);

    //Texts
    sf::Text Items("Items", Font), Spells("Spells", Font), Stats("Stats", Font), Quests("Quests", Font), Exit("Exit", Font),
        PointsText("Points left: " + IntToString(player.GetTalentPoints()), Font),
        HealthText("Health: " + IntToString(player.GetHealth()) + "/" + IntToString(player.GetMaxHealth()), Font),
        PowerText("", Font),
        IntStrText("", Font),
        AttackText("Attack: " + IntToString(player.GetAttack()), Font), 
        DefenseText("Defense: " + IntToString(player.GetDefense()), Font);

    ScreenTexture.Draw(BackgroundSprite);

    float SpellTextY = 50;
    for(auto itr = player.GetSpells().begin(); itr != player.GetSpells().end(); ++itr)
    {
        sf::Text SpellText(itr->Name, Font);
        SpellText.SetPosition(830, SpellTextY);
        SpellText.SetColor(sf::Color(0, 0, 0));
        SpellText.SetStyle(sf::Text::Bold);
        SpellTextY += 35;
        ScreenTexture.Draw(SpellText);
    }

    if(player.GetClass() == CLASS_WARRIOR)
    {
        PowerText.SetString("Stamina: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));
        IntStrText.SetString("Strenght: " + IntToString(player.GetIntStr()));
    }
    else
    {
        PowerText.SetString("Mana: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));
        IntStrText.SetString("Intelligence: " + IntToString(player.GetIntStr()));
    }

    PointsText.SetPosition(480, 55);
    HealthText.SetPosition(480, 90);
    PowerText.SetPosition(480, 125);
    AttackText.SetPosition(480, 160);
    DefenseText.SetPosition(480, 195);
    IntStrText.SetPosition(480, 230);
    Items.SetPosition(890.0f, 580.0f);
    Spells.SetPosition(890.0f, 615.0f);
    Stats.SetPosition(890.0f, 650.0f);
    Quests.SetPosition(890.0f, 685.0f);
    Exit.SetPosition(890.0f, 720.0f);

    PointsText.SetColor(sf::Color(0, 0, 0));
    HealthText.SetColor(sf::Color(0, 0, 0));
    PowerText.SetColor(sf::Color(0, 0, 0));
    AttackText.SetColor(sf::Color(0, 0, 0));
    DefenseText.SetColor(sf::Color(0, 0, 0));
    IntStrText.SetColor(sf::Color(0, 0, 0));
    Items.SetColor(sf::Color(0, 0, 0));
    Spells.SetColor(sf::Color(0, 0, 0));
    Stats.SetColor(sf::Color(0, 0, 0));
    Quests.SetColor(sf::Color(0, 0, 0));
    Exit.SetColor(sf::Color(0, 0, 0));

    PointsText.SetStyle(sf::Text::Bold);
    HealthText.SetStyle(sf::Text::Bold);
    PowerText.SetStyle(sf::Text::Bold);
    AttackText.SetStyle(sf::Text::Bold);
    DefenseText.SetStyle(sf::Text::Bold);
    IntStrText.SetStyle(sf::Text::Bold);
    Items.SetStyle(sf::Text::Bold);
    Spells.SetStyle(sf::Text::Bold);
    Stats.SetStyle(sf::Text::Bold);
    Quests.SetStyle(sf::Text::Bold);
    Exit.SetStyle(sf::Text::Bold);

    ScreenTexture.Draw(PlayerSprite);
    ScreenTexture.Draw(PointsText);
    ScreenTexture.Draw(HealthText);
    ScreenTexture.Draw(PowerText);
    ScreenTexture.Draw(IntStrText);
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
    Font.LoadFromFile("Graphics/papyrus.ttf");
    sf::Texture ArrowTexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow2.png");
    ArrowSprite.SetTexture(ArrowTexture);
    ArrowSprite.SetPosition(840.0f, 580.0f);
    DrawTexture();
    int Command = 1;
    float ArrowY = 580.0f;
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
                    ArrowSprite.SetPosition(840.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Command != 5)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(840.0f, ArrowY);
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
                ArrowSprite.SetPosition(840.0f, ArrowY);
            }
        }
        Window.Clear();
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
        Window.Draw(sf::Sprite(ScreenTexture.GetTexture()));
        Window.Draw(ArrowSprite);
        DrawItems();
        Window.Display();
    }
}