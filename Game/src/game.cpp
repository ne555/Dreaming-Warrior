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
    Window.Create(sf::VideoMode(32*32, 24*32, 32), "Dreaming Warrior", sf::Style::Close);
    Window.SetFramerateLimit(60);
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

    switch(Player.LoadFromFile(World, MenuResult.PlayerClass, ThisIsHack))
    {
    case CLASS_WARRIOR:
        PlayerTexture.LoadFromFile("Tiles/Warrior.png");
        break;
    case CLASS_MAGE:
        PlayerTexture.LoadFromFile("Tiles/Mage.png");
        break;
    }
    LoadMap(Player.Map);
}

void Game::GameOver()
{
    sf::Font Font;
    Font.LoadFromFile("Graphics/papyrus.ttf");
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    BackgroundTexture.LoadFromFile("Graphics/MainMenu.jpg");
    BackgroundSprite.SetTexture(BackgroundTexture);
    sf::Text GameOver("Game Over...", Font, 90U);
    GameOver.SetStyle(sf::Text::Bold);
    GameOver.SetPosition(300, 320);

    sf::Event Event;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if(Event.Type == sf::Event::KeyPressed)
            {
                exit(0);
            }
        }
        Window.Clear();
        Window.Draw(BackgroundSprite);
        Window.Draw(GameOver);
        Window.Display();
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

    Player.SetHealth(Player.GetHealth() + 2);
    Player.SetPower(Player.GetPower() + 2);

    if(urand(0, 100) < 5)
       return 1;

    return 0;
}

void Game::GameLoop()
{
    sf::Texture HideHack;
    HideHack.LoadFromFile("Tiles/Hack.png");
    for(int y=0; y<24; ++y)
    {
        for(int x=0; x<32; ++x)
        {
            HideMapHack[y][x].SetTexture(HideHack);
            HideMapHack[y][x].SetPosition(x*32, y*32);
        }
    }
    while(Window.IsOpen()) 
    {
        sf::Event Event;
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                SaveMap(PathToMap);
                SavePlayer();
                return;
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                switch(Move(NORTH))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(NORTH);
                    break;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                switch(Move(SOUTH))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(SOUTH);
                    break;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Right))
            {
                switch(Move(WEST))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(WEST);
                    break;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Left))
            {
                switch(Move(EAST))
                {
                case 0:
                    break;
                case 1:
                    RandomEncounter();
                    break;
                case 2:
                    Encounter(EAST);
                    break;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::C))
            {
                CharacterScreen Screen(Player, Window);
                Screen.MainLoop();
            }
        }
        Window.Clear();
        DrawAll();
        Window.Display();
    }
}