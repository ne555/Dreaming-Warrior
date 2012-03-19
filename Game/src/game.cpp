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
#include "game.h"

Game::Game()
{
    Window.create(sf::VideoMode(32*32, 24*32, 32), "Dreaming Warrior", sf::Style::Close);
    Window.setFramerateLimit(60);
}

MainMenuData Game::ShowMenu()
{
    MainMenu Menu(Window);
    return Menu.MainLoop();
}

void Game::InitGame(MainMenuData MenuResult)
{
    bool ThisIsHack = false;
    switch(MenuResult.Mode)
    {
    case NEW_GAME:
        //TODO: save po nekom imenu [PH]
        ThisIsHack = true;
        World = "SavedGame";
        CopyWorld(MenuResult.PathToWorld, World);
        break;
    case LOAD_GAME:
        //TODO: save po nekom imenu [PH]
        World = "SavedGame";
        break;
    }
    Font.loadFromFile("Graphics/papyrus.ttf");

    switch(Player.loadFromFile(World, MenuResult.PlayerClass, ThisIsHack, MenuResult.PlayerName))
    {
    case CLASS_WARRIOR:
        PlayerTexture.loadFromFile("Tiles/Warrior.png");
        break;
    case CLASS_MAGE:
        PlayerTexture.loadFromFile("Tiles/Mage.png");
        break;
    }
    LoadMap(Player.Map);
}

void Game::GameOver()
{
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    BackgroundTexture.loadFromFile("Graphics/MainMenu.jpg");
    BackgroundSprite.setTexture(BackgroundTexture);
    sf::Text GameOver("Game Over...", Font, 90U);
    GameOver.setStyle(sf::Text::Bold);
    GameOver.setPosition(300, 320);

    sf::Event Event;
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if(Event.type == sf::Event::KeyPressed)
            {
                exit(0);
            }
        }
        Window.clear();
        Window.draw(BackgroundSprite);
        Window.draw(GameOver);
        Window.display();
    }
}

/*
return 0; nista
return 1; random encounter
return 2; creature interaction
*/
int Game::Move(Orientation Direction)
{
    switch(Direction)
    {
    case NORTH:
        Player.InteractsWith = ObjectGrid[Player.GetY()/32-1][Player.GetX()/32];
        break;
    case SOUTH:
        Player.InteractsWith = ObjectGrid[Player.GetY()/32+1][Player.GetX()/32];
        break;
    case EAST:
        Player.InteractsWith = ObjectGrid[Player.GetY()/32][Player.GetX()/32-1];
        break;
    case WEST:
        Player.InteractsWith = ObjectGrid[Player.GetY()/32][Player.GetX()/32+1];
        break;
    }

    if(Player.InteractsWith != NO_OBJECT)
        return 2;

    switch(Direction)
    {
    case NORTH:
        if(CheckPortals(Player.GetX(), Player.GetY()-32))
            return 0;
        if(!UpdateMovement(Player.GetX(), Player.GetY()-32, Direction))
            break;
        Player.SetY(Player.GetY() - 32);
        break;
    case SOUTH:
        if(CheckPortals(Player.GetX(), Player.GetY()+32))
            return 0;
        if(!UpdateMovement(Player.GetX(), Player.GetY()+32, Direction))
            break;
        Player.SetY(Player.GetY() + 32);
        break;
    case WEST:
        if(CheckPortals(Player.GetX()+32, Player.GetY()))
            return 0;
        if(!UpdateMovement(Player.GetX()+32, Player.GetY(), Direction))
            break;
        Player.SetX(Player.GetX() + 32);
        break;
    case EAST:
        if(CheckPortals(Player.GetX()-32, Player.GetY()))
            return 0;
        if(!UpdateMovement(Player.GetX()-32, Player.GetY(), Direction))
            break;
        Player.SetX(Player.GetX() - 32);
        break;
    }

    Player.SetHealth(Player.GetHealth() + 1);
    Player.SetPower(Player.GetPower() + 1);

    if(urand(0, 100) < 15)
       return 1;

    return 0;
}

void Game::GameLoop()
{
    sf::Texture HideHack;
    HideHack.loadFromFile("Tiles/Hack.png");
    for(int y=0; y<24; ++y)
    {
        for(int x=0; x<32; ++x)
        {
            HideMapHack[y][x].setTexture(HideHack);
            HideMapHack[y][x].setPosition((float)x*32, (float)y*32);
        }
    }
    while(Window.isOpen()) 
    {
        sf::Event Event;
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::Closed) || ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)))
            {
                SaveMap(PathToMap);
                SavePlayer();
                return;
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                switch(Move(NORTH))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(0, -1);
                    break;
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                switch(Move(SOUTH))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(0, 1);
                    break;
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
            {
                switch(Move(WEST))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(1, 0);
                    break;
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
            {
                switch(Move(EAST))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(-1, 0);
                    break;
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::C))
            {
                CharacterScreen Screen(Player, Window);
                Screen.MainLoop();
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S))
            {
                SaveMap(PathToMap);
                SavePlayer();
            }
        }
        Window.clear();
        DrawAll();
        Window.display();
    }
}