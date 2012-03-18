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
    list<Vendor> Vendors;
    list<QuestGiver> QuestGivers;
    vector<Enemy> RandomEncounters;

    sf::Texture MapTexture;
    string World;
    string PathToMap;

    struct Portal
    {
        Portal(int x, int y, string Path, int px, int py)
        {
            PortalRect.width = 32;
            PortalRect.height = 32;
            PortalRect.left = x*32;
            PortalRect.top = y*32;
            PlayerNewX = px*32;
            PlayerNewY = py*32;
            PathToMap = Path;
        }
        string PathToMap;
        sf::IntRect PortalRect;
        int PlayerNewX;
        int PlayerNewY;
    };
    vector<Portal> Portals;
    sf::Font Font;
    sf::Texture PlayerTexture;

    void LoadMap(string PathToMap);
    void CopyWorld(const boost::filesystem::path& source, const boost::filesystem::path& dest);
    void SaveMap(string PathToMap);
    void SavePlayer();
    bool CheckCollision(int x, int y, Orientation Direction);

    void GameOver();

    ObjectType ObjectGrid[24][32];
    sf::Sprite HideMapHack[24][32]; //this is so wrong

public:
    Game();

    MainMenuData ShowMenu();
    void InitGame(MainMenuData MenuResult);
    void GameLoop();

    int Move(Orientation Direction);
    bool UpdateMovement(int x, int y, Orientation Direction);
    bool CheckPortals(int x, int y);
};

#endif