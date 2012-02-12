/*
    This file is part of Game Project.

    Game Project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Game Project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Game Project.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "mainmenu.h"

MainMenu::MainMenu(sf::RenderWindow &Window)
    : Window(Window)
{
    Background.LoadFromFile("Graphics/MainMenu.png");
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
    //ovdje se nesmije bit
}

Class MainMenu::ChooseClass()
{
    int Command = 1;
    sf::Texture MageTexture, WarriorTexture, ArrowTexture;
    MageTexture.LoadFromFile("Graphics/Mage.png");
    WarriorTexture.LoadFromFile("Graphics/Warrior.png");
    ArrowTexture.LoadFromFile("Graphics/Strelica.png");
    sf::Sprite MageSprite(MageTexture), WarriorSprite(WarriorTexture), ArrowSprite(ArrowTexture);
    //MageSprite.SetPosition();
    //WarriorSprite.SetPosition();
    ArrowSprite.SetPosition(65.0f, 450.0f);
    sf::Text
        MageText("Mage"),
        WarriorText("Warrior");
    MageText.SetPosition(90, 450);
    WarriorText.SetPosition(800, 450);

    sf::Event Event;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Left))
            {
                if(Command != 1)
                {
                    --Command;
                    ArrowSprite.SetPosition(65.0f, 450.0f);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Right))
            {
                if(Command != 2)
                {
                    ++Command;
                    ArrowSprite.SetPosition(755.0f, 450.0f);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(Command)
                {
                case 1:
                    return CLASS_MAGE;
                case 2:
                    return CLASS_WARRIOR;
                case 3:
                    exit(0);
                }
            }
        }
        Window.Clear();
        Window.Draw(sf::Sprite(Background));
        Window.Draw(MageSprite);
        Window.Draw(WarriorSprite);
        Window.Draw(MageText);
        Window.Draw(WarriorText);
        Window.Draw(ArrowSprite);
        Window.Display();
    }
}

GameMode MainMenu::ChooseGameMode()
{
    float ArrowY = 350;
    int Command = 1;
    sf::Text
        NewGame("Nova igra"),
        LoadGame("Ucitaj igru"),
        Exit("Izlaz");
    
    NewGame.SetPosition(450, 350);
    LoadGame.SetPosition(450, 385);
    Exit.SetPosition(450, 420);
    
    NewGame.SetColor(sf::Color(255, 255, 255));
    LoadGame.SetColor(sf::Color(255, 255, 255));
    Exit.SetColor(sf::Color(255, 255, 255));

    sf::Texture ArrowTexture;
    ArrowTexture.LoadFromFile("Graphics/Strelica.png");
    sf::Sprite ArrowSprite(ArrowTexture);
    ArrowSprite.SetPosition(410.0f, ArrowY);

    sf::Event Event;
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
                    ArrowSprite.SetPosition(410.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Command != 3)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(410.0f, ArrowY);
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
    //ovdje nesmijes biti
}