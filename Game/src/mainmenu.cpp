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
#include "mainmenu.h"

MainMenu::MainMenu(sf::RenderWindow &Window)
    : Window(Window)
{
    Background.LoadFromFile("Graphics/MainMenu.jpg");
}

MainMenuData MainMenu::MainLoop()
{
    switch(ChooseGameMode())
    {
    case NEW_GAME:
        {
            MainMenuData MenuData;
            MenuData.Mode = NEW_GAME;
            MenuData.PathToWorld = "World";
            MenuData.PlayerClass = ChooseClass();
            return MenuData;
        }
    case LOAD_GAME:
        {
            MainMenuData MenuData;
            MenuData.Mode = LOAD_GAME;
            return MenuData;
        }
    }
    cerr << "FATAL: Invalid game mode." << endl;
    exit(1);
}

Class MainMenu::ChooseClass()
{
    Class PlayerClass = CLASS_MAGE;
    sf::Texture MageTexture, WarriorTexture, ArrowTexture;
    MageTexture.LoadFromFile("Graphics/Mage.png");
    WarriorTexture.LoadFromFile("Graphics/Warrior.png");
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
    sf::Sprite MageSprite(MageTexture), WarriorSprite(WarriorTexture), ArrowSprite(ArrowTexture);
    MageSprite.SetPosition(80.0f, 190.0f);
    WarriorSprite.SetPosition(80.0f, 190.0f);
    ArrowSprite.SetPosition(400.0f, 350.0f);
    sf::Text
        MageText("Mage", Font),
        WarriorText("Warrior", Font);
    MageText.SetPosition(450.0f, 350.0f);
    WarriorText.SetPosition(450.0f, 385.0f);

    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(PlayerClass != CLASS_MAGE)
                {
                    PlayerClass = CLASS_MAGE;
                    ArrowSprite.SetPosition(400.0f, 350.0f);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(PlayerClass != CLASS_WARRIOR)
                {
                    PlayerClass = CLASS_WARRIOR;
                    ArrowSprite.SetPosition(400.0f, 385.0f);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                return PlayerClass;
            }
        }
        Window.Clear();
        Window.Draw(sf::Sprite(Background));
        switch(PlayerClass)
        {
        case CLASS_MAGE:
            Window.Draw(MageSprite);
            break;
        case CLASS_WARRIOR:
            Window.Draw(WarriorSprite);
            break;
        }
        Window.Draw(MageText);
        Window.Draw(WarriorText);
        Window.Draw(ArrowSprite);
        Window.Display();
    }
}

GameMode MainMenu::ChooseGameMode()
{
    Font.LoadFromFile("Graphics/papyrus.ttf");
    float ArrowY = 350;
    int Command = 1;
    sf::Text
        NewGame("Nova igra", Font),
        LoadGame("Ucitaj igru", Font),
        Exit("Izlaz", Font);
    
    NewGame.SetPosition(450, 350);
    LoadGame.SetPosition(450, 385);
    Exit.SetPosition(450, 420);
    
    NewGame.SetColor(sf::Color(255, 255, 255));
    LoadGame.SetColor(sf::Color(255, 255, 255));
    Exit.SetColor(sf::Color(255, 255, 255));

    sf::Texture ArrowTexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
    sf::Sprite ArrowSprite(ArrowTexture);
    ArrowSprite.SetPosition(400.0f, ArrowY);

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
                    ArrowSprite.SetPosition(400.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Command != 3)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(400.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(Command)
                {
                case 1:
                    return NEW_GAME;
                case 2:
                    return LOAD_GAME;
                case 3:
                    exit(0);
                }
            }
        }
        Window.Clear();
        Window.Draw(sf::Sprite(Background));
        Window.Draw(ArrowSprite);
        Window.Draw(NewGame);
        Window.Draw(LoadGame);
        Window.Draw(Exit);
        Window.Display();
    }
}