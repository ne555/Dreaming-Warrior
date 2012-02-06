#ifndef GAME_H
#define GAME_H

class Game;

#include "player.h"
#include "Include.h"
#include "enemy.h"
#include "mainmenu.h"
#include "characterscreen.h"
#include "vendor.h"
#include "questgiver.h"

class Game
{
    sf::RenderWindow Window;
    Player Player;

    void RandomEncounter();
    void Encounter(Orientation Direction);

    void DrawAll();
    vector<Enemy> Enemies;
    vector<Vendor> Vendors;
    vector<QuestGiver> QuestGivers;
    vector<Enemy> RandomEncounters;

    sf::Texture MapTexture;
    string World;

    struct Portal
    {
        Portal(int x, int y, string Path, int px, int py)
        {
            PortalRect.Width = 32;
            PortalRect.Height = 32;
            PortalRect.Left = x;
            PortalRect.Top = y;
            PlayerNewX = px;
            PlayerNewY = py;
            PathToMap = Path;
        }
        string PathToMap;
        sf::IntRect PortalRect;
        int PlayerNewX;
        int PlayerNewY;
    };
    vector<Portal> Portals;
    sf::Texture PlayerTexture;

    void LoadMap(string PathToMap);
    bool CheckCollision(int x, int y, Orientation Direction);

    //todo: samo jedan object grid na kojem su i creature i drva i objekti
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