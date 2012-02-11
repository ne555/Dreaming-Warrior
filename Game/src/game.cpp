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
#include "game.h"

Game::Game()
{
    Window.Create(sf::VideoMode(32*32, 24*32, 32), "The Game", sf::Style::Close);
    Window.SetFramerateLimit(30);
}

Game::~Game()
{
}

MainMenuData Game::ShowMenu()
{
    MainMenu Menu(Window);
    return Menu.MainLoop();
}

void Game::InitGame(MainMenuData MenuResult)
{
    switch(MenuResult.Mode)
    {
    case NEW_GAME:
        //TODO: save po nekom imenu [PH]
        World = "SavedGames/Save1";
        CopyWorld(MenuResult.PathToWorld, World);
        break;
    case LOAD_GAME:
        //TODO: save po nekom imenu [PH]
        World = "SavedGames/Save1";
        break;
    }
    Player.LoadFromFile(World);
    LoadMap(World + "/Map1/");
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

    //TODO: Random encounter
    //if(urand(0, 1) == 0)
        //return 1;

    return 0;
}

void Game::GameLoop()
{
    while(Window.IsOpen()) 
    {
        sf::Event Event;
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
                return;
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
            }
        }
        Window.Clear();
        DrawAll();
        Window.Display();
    }
}