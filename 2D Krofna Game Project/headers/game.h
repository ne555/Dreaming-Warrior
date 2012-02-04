#ifndef GAME_H
#define GAME_H

class Game;

#include "player.h"
#include "Include.h"
#include "enemy.h"
#include "mainmenu.h"
#include "backpackscreen.h"
#include "vendor.h"
#include "questgiver.h"

class Game
{
    sf::RenderWindow Window;
    Player Player;

    void ShowCharacterScreen();
    void ShowBackpackScreen();

    void RandomEncounter();
    void Encounter(Orientation Direction);

    void DrawAll();
    std::vector<Enemy> Enemies;
    std::vector<Vendor> Vendors;
    std::vector<QuestGiver> QuestGivers;
    std::vector<Enemy> RandomEncounters;

    sf::Texture MapTexture;
    std::string World;

    struct Portal
    {
        Portal(int x, int y, std::string Path, int px, int py)
        {
            PortalRect.Width = 32;
            PortalRect.Height = 32;
            PortalRect.Left = x;
            PortalRect.Top = y;
            PlayerNewX = px;
            PlayerNewY = py;
            PathToMap = Path;
        }
        std::string PathToMap;
        sf::IntRect PortalRect;
        int PlayerNewX;
        int PlayerNewY;
    };
    std::vector<Portal> Portals;
    sf::Texture PlayerTexture;

    void LoadMap(std::string PathToMap);
    bool CheckCollision(int x, int y, Orientation Direction);

    CreatureType CreatureGrid[24][32];
    bool CollisionGrid[24][32];

public:
    Game();
    ~Game();

    MainMenuData ShowMenu();
    void InitGame(MainMenuData MenuResult);
    void GameLoop();

    int Move(Orientation Direction);
    bool UpdateMovement(int x, int y, Orientation Direction);
    bool CheckPortals(int x, int y);
};

#endif