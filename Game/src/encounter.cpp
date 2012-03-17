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
#include "combat.h"
#include "VendorEncounter.h"
#include "QuestEncounter.h"

void Game::Encounter(Orientation Direction)
{
    int x, y;

    switch(Direction)
    {
    case NORTH:
        x = 0;
        y = -1;
        break;
    case SOUTH:
        x = 0;
        y = 1;
        break;
    case WEST:
        x = 1;
        y = 0;
        break;
    case EAST:
        x = -1;
        y = 0;
        break;
    }

    switch(Player.InteractsWith)
    {
    case ENEMY:
        for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
        {
            if(itr->GetX() == Player.GetX()/32 + x && itr->GetY() == Player.GetY()/32 + y)
            {
                Combat Combat(Window, Player, *itr);
                switch(Combat.MainLoop())
                {
                case 0:
                    GameOver();
                case 1:
                    ObjectGrid[itr->GetY()][itr->GetX()] = NO_OBJECT;
                    Enemies.erase(itr);
                    break;
                case 2:
                    break;
                }
                return;
            }
        }
        break;
    case VENDOR:
        for(auto itr = Vendors.begin(); itr != Vendors.end(); ++itr)
        {
            if(itr->x == Player.GetX()/32 + x && itr->y == Player.GetY()/32 + y)
            {
                VendorEncounter VendorEncounter(Player, Window, *itr);
                VendorEncounter.MainLoop();
                return;
            }
        }
        break;
    case QUEST:
        for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
        {
            if(itr->x == Player.GetX()/32 + x && itr->y == Player.GetY()/32 + y)
            {
                QuestEncounter QuestEncounter(Player, Window);
                QuestGiver QuestGiver = QuestEncounter.MainLoop(*itr);
                QuestGivers.erase(itr);
                QuestGivers.push_back(QuestGiver);
                return;
            }
        }
        break;
    }
}

void Game::RandomEncounter()
{
    if(RandomEncounters.empty())
        return;
    auto itr = RandomEncounters.begin() + urand(0, RandomEncounters.size()-1);
    Combat Combat(Window, Player, *itr);
    switch(Combat.MainLoop())
    {
    case 0:
        GameOver();
        break;
    case 1:
        RandomEncounters.erase(itr);
        break;
    case 2:
        break;
    }
}