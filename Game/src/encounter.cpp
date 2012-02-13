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
    switch(Direction)
    {
    case NORTH:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
            {
                if(itr->GetX() == Player.GetX()/32 && itr->GetY() == Player.GetY()/32-1)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        GameOver();
                    case 1:
                        ObjectGrid[itr->GetY()][itr->GetX()] = NO_OBJECT;
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
            for(auto itr = Vendors.begin(); itr != Vendors.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
                {
                    VendorEncounter VendorEncounter;
                    Vendor Vendor = VendorEncounter.MainLoop(Player, *itr);
                    Vendors.erase(itr);
                    Vendors.push_back(Vendor);
                    return;
                }
            }
            break;
        case QUEST:
            for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
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
        break;
    case SOUTH:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
            {
                if(itr->GetX() == Player.GetX()/32 && itr->GetY() == Player.GetY()/32+1)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        GameOver();
                    case 1:
                        ObjectGrid[itr->GetY()][itr->GetX()] = NO_OBJECT;
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
            for(auto itr = Vendors.begin(); itr != Vendors.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
                {
                    VendorEncounter VendorEncounter;
                    Vendor Vendor = VendorEncounter.MainLoop(Player, *itr);
                    Vendors.erase(itr);
                    Vendors.push_back(Vendor);
                    return;
                }
            }
            break;
        case QUEST:
            for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
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
        break;
    case WEST:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
            {
                if(itr->GetX() == Player.GetX()/32+1 && itr->GetY() == Player.GetY()/32)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        GameOver();
                    case 1:
                        ObjectGrid[itr->GetY()][itr->GetX()] = NO_OBJECT;
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
            for(auto itr = Vendors.begin(); itr != Vendors.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
                {
                    VendorEncounter VendorEncounter;
                    Vendor Vendor = VendorEncounter.MainLoop(Player, *itr);
                    Vendors.erase(itr);
                    Vendors.push_back(Vendor);
                    return;
                }
            }
            break;
        case QUEST:
            for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
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
        break;
    case EAST:
        switch(Player.InteractsWith)
        {
        case ENEMY:
            for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
            {
                if(itr->GetX() == Player.GetX()/32-1 && itr->GetY() == Player.GetY()/32)
                {
                    Combat Combat(Window, Player, *itr);
                    switch(Combat.MainLoop())
                    {
                    case 0:
                        GameOver();
                    case 1:
                        ObjectGrid[itr->GetY()][itr->GetX()] = NO_OBJECT;
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
            for(auto itr = Vendors.begin(); itr != Vendors.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
                {
                    VendorEncounter VendorEncounter;
                    Vendor Vendor = VendorEncounter.MainLoop(Player, *itr);
                    Vendors.erase(itr);
                    Vendors.push_back(Vendor);
                    return;
                }
            }
            break;
        case QUEST:
            for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
            {
                if(itr->x == Player.GetX()/32 && itr->y == Player.GetY()/32-1)
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
        break;
    }
}

void Game::RandomEncounter()
{
    if(RandomEncounters.empty())
        return;
    vector<Enemy>::iterator itr = RandomEncounters.begin() + urand(0, RandomEncounters.size()-1);
    Combat Combat(Window, Player, *itr);
    Combat.MainLoop() ? RandomEncounters.erase(itr) : GameOver();
    //TODO: NE ZABORAVI Quest objective i loot!
}