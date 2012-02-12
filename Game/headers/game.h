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
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "Include.h"
#include "enemy.h"
#include "mainmenu.h"
#include "characterscreen.h"
#include "vendor.h"
#include "questgiver.h"
#include <boost\filesystem.hpp>

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
    string PathToMap;

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
    void CopyWorld(const boost::filesystem::path& source, const boost::filesystem::path& dest);
    void SaveMap(string PathToMap);
    void SavePlayer();
    bool CheckCollision(int x, int y, Orientation Direction);

    ObjectType ObjectGrid[24][32];

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