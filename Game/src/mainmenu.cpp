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
    Background.loadFromFile("Graphics/MainMenu.jpg");
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
            MenuData.PlayerName = ChooseName();
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

string MainMenu::ChooseName()
{
    string PlayerName;
    sf::Text PlayerNameText("", Font), ChooseNameText("Enter name for your character: ", Font);
    ChooseNameText.setColor(sf::Color::Black);
    ChooseNameText.setPosition(350, 80);
    PlayerNameText.setPosition(350, 150);
    PlayerNameText.setColor(sf::Color::Black);
    sf::Texture BackgroundTexture;
    BackgroundTexture.loadFromFile("Graphics/Name.png");
    sf::Sprite BackgroundSprite(BackgroundTexture);

    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Back) && !PlayerName.empty())
            {
                PlayerName.erase(PlayerName.end()-1);
                PlayerNameText.setString(PlayerName);
            }
            else if(Event.type == sf::Event::TextEntered) 
            {
                if(Event.text.unicode > 64) 
                {

                    PlayerName += static_cast<char>(Event.text.unicode); 
                    PlayerNameText.setString(PlayerName);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                return PlayerName;
            }
        }
        Window.clear();
        Window.draw(BackgroundSprite);
        Window.draw(PlayerNameText);
        Window.draw(ChooseNameText);
        Window.display();
    }
}

Class MainMenu::ChooseClass()
{
    Class PlayerClass = CLASS_MAGE;
    sf::Texture MageTexture, WarriorTexture, ArrowTexture;
    MageTexture.loadFromFile("Graphics/Mage.png");
    WarriorTexture.loadFromFile("Graphics/Warrior.png");
    ArrowTexture.loadFromFile("Graphics/Arrow.png");
    sf::Sprite MageSprite(MageTexture), WarriorSprite(WarriorTexture), ArrowSprite(ArrowTexture);
    MageSprite.setPosition(80.0f, 190.0f);
    WarriorSprite.setPosition(80.0f, 190.0f);
    ArrowSprite.setPosition(400.0f, 350.0f);
    sf::Text
        MageText("Mage", Font),
        WarriorText("Warrior", Font);
    MageText.setStyle(sf::Text::Bold);
    WarriorText.setStyle(sf::Text::Bold);
    MageText.setPosition(450.0f, 350.0f);
    WarriorText.setPosition(450.0f, 385.0f);

    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(PlayerClass != CLASS_MAGE)
                {
                    PlayerClass = CLASS_MAGE;
                    ArrowSprite.setPosition(400.0f, 350.0f);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(PlayerClass != CLASS_WARRIOR)
                {
                    PlayerClass = CLASS_WARRIOR;
                    ArrowSprite.setPosition(400.0f, 385.0f);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                return PlayerClass;
            }
        }
        Window.clear();
        Window.draw(sf::Sprite(Background));
        switch(PlayerClass)
        {
        case CLASS_MAGE:
            Window.draw(MageSprite);
            break;
        case CLASS_WARRIOR:
            Window.draw(WarriorSprite);
            break;
        }
        Window.draw(MageText);
        Window.draw(WarriorText);
        Window.draw(ArrowSprite);
        Window.display();
    }
}

GameMode MainMenu::ChooseGameMode()
{
    Font.loadFromFile("Graphics/papyrus.ttf");
    float ArrowY = 300;
    int Command = 1;
    sf::Text
        NewGame("New Game", Font),
        LoadGame("Load Game", Font),
        Exit("Exit", Font);
    
    NewGame.setPosition(400, 300);
    LoadGame.setPosition(400, 335);
    Exit.setPosition(400, 370);

    NewGame.setStyle(sf::Text::Bold);
    LoadGame.setStyle(sf::Text::Bold);
    Exit.setStyle(sf::Text::Bold);

    sf::Texture ArrowTexture;
    ArrowTexture.loadFromFile("Graphics/Arrow.png");
    sf::Sprite ArrowSprite(ArrowTexture);
    ArrowSprite.setPosition(350.0f, ArrowY);

    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(Command != 1)
                {
                    --Command;
                    ArrowY -= 35;
                    ArrowSprite.setPosition(350.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(Command != 3)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.setPosition(350.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
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
        Window.clear();
        Window.draw(sf::Sprite(Background));
        Window.draw(ArrowSprite);
        Window.draw(NewGame);
        Window.draw(LoadGame);
        Window.draw(Exit);
        Window.display();
    }
}