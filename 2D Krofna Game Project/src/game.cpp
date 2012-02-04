#include "game.h"
#include "combat.h"

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
    MainMenu Menu;
    return Menu.MainLoop();
}

void Game::InitGame(MainMenuData MenuResult)
{
    //ph
    Player.LoadFromFile(MenuResult.PlayerCfgFileName);
    World = MenuResult.World;
    LoadMap(World + "/Map1/");
    switch(MenuResult.Result)
    {
    case EXIT:
        exit(0);
    }
}

void Game::DrawAll()
{
    Window.Draw(sf::Sprite(MapTexture));
    sf::Sprite PlayerSprite(PlayerTexture);
    PlayerSprite.SetPosition((float)Player.GetX(), (float)Player.GetY());
    Window.Draw(PlayerSprite);

    for(auto itr = Enemies.begin(); itr != Enemies.end(); itr++)
    {
        sf::Sprite Sprite(itr->CreatureMapTexture);
        Sprite.SetPosition((float)itr->GetX()*32, (float)itr->GetY()*32);
        Window.Draw(Sprite);
    }
}

void Game::RandomEncounter()
{
    if(RandomEncounters.empty())
        return;
    std::vector<Enemy>::iterator itr = RandomEncounters.begin() + urand(0, RandomEncounters.size()-1);
    Combat Combat(Window, Player, *itr);
    if(Combat.MainLoop())
        RandomEncounters.erase(itr);
    else
        std::cout << "Game over...";//PH!
}

void Game::Encounter(Orientation Direction)
{
    switch(Direction)
    {
    case NORTH:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); itr++)
            {
                if(itr->GetX() == Player.GetX()/32 && itr->GetY() == Player.GetY()/32-1)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        std::cout << "[PH] Game Over";
                        break;
                    case 1:
                        CreatureGrid[itr->GetY()][itr->GetX()] = NO_CREATURE;
                        Enemies.erase(itr);
                        //bla bla quest objective, drop loot je u combatu hendlan
                        break;
                    case 2:
                        break;
                    }
                    return;
                }
            }
            break;
        case VENDOR:
            break;
            //...
        }
        break;
    case SOUTH:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); itr++)
            {
                if(itr->GetX() == Player.GetX()/32 && itr->GetY() == Player.GetY()/32+1)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        std::cout << "[PH] Game Over";
                        break;
                    case 1:
                        CreatureGrid[itr->GetY()][itr->GetX()] = NO_CREATURE;
                        Enemies.erase(itr);
                        //bla bla quest objective, drop loot je u combatu hendlan
                        break;
                    case 2:
                        break;
                    }
                    return;
                }
            }
            break;
        case VENDOR:
            break;
            //...
        }
        break;
    case WEST:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); itr++)
            {
                if(itr->GetX() == Player.GetX()/32+1 && itr->GetY() == Player.GetY()/32)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        std::cout << "[PH] Game Over";
                        break;
                    case 1:
                        CreatureGrid[itr->GetY()][itr->GetX()] = NO_CREATURE;
                        Enemies.erase(itr);
                        //bla bla quest objective, drop loot je u combatu hendlan
                        break;
                    case 2:
                        break;
                    }
                    return;
                }
            }
            break;
        case VENDOR:
            break;
            //...
        }
        break;
    case EAST:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); itr++)
            {
                if(itr->GetX() == Player.GetX()/32-1 && itr->GetY() == Player.GetY()/32)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        std::cout << "[PH] Game Over";
                        break;
                    case 1:
                        CreatureGrid[itr->GetY()][itr->GetX()] = NO_CREATURE;
                        Enemies.erase(itr);
                        //bla bla quest objective, drop loot je u combatu hendlan
                        break;
                    case 2:
                        break;
                    }
                    return;
                }
            }
            break;
        case VENDOR:
            break;
            //...
        }
        break;
    }
}
/*
TODO: Pokazi lika, equipane iteme, questove i statse
//i ovo class jer treba swap izmeðu questova
*/
void Game::ShowCharacterScreen()
{
    sf::Texture BackgroundTexture;
    //BackgroundTexture.LoadFromFile("");
    sf::Sprite BackgroundSprite(BackgroundTexture);
    sf::Texture PlayerTexture;
    //PlayerTexture.LoadFromFile("");
    sf::Sprite PlayerSprite(PlayerTexture);
    //PlayerSprite.SetPosition();

    // bla bla PH
}
/*
TODO: Pokazi lika, backpack iteme, omoguci mjenjanje statsa, omoguci mjenjanje equipa
*/
void Game::ShowBackpackScreen()
{
    BackpackScreen Screen(Player);
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
        Player.InteractsWith = CreatureGrid[Player.GetY()/32-1][Player.GetX()/32];
    case SOUTH:
        Player.InteractsWith = CreatureGrid[Player.GetY()/32+1][Player.GetX()/32];
    case EAST:
        Player.InteractsWith = CreatureGrid[Player.GetY()/32][Player.GetX()/32-1];
    case WEST:
        Player.InteractsWith = CreatureGrid[Player.GetY()/32][Player.GetX()/32+1];
    }

    if(Player.InteractsWith != NO_CREATURE)
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
                ShowCharacterScreen();
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::B))
            {
                ShowBackpackScreen();
            }
        }
        Window.Clear();
        DrawAll();
        Window.Display();
    }
}