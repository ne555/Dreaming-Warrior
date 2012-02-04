#ifndef MAP_H
#define MAP_H

class Map;

#include <SFML\Graphics.hpp>
#include "game.h"

class Map
{
    sf::RenderWindow &MapWindow;
    Game &myGame;
    sf::Texture MapTexture;
    std::string World;

    bool CollisionTable[24][32];

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

public:
    Map(sf::RenderWindow &Window, std::string PathToMap, Game &myGame);

    CreatureType CreatureTable[24][32];

    bool UpdateMovement(int x, int y, Orientation Direction);
    bool CheckPortals(int x, int y, Player &pPlayer);
    CreatureType CheckCreatures(int x, int y, Orientation Direction);
    void ShowPlayer(int x, int y);
};

#endif