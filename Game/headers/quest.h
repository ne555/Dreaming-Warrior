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
#ifndef QUEST_H
#define QUEST_H

#include "Include.h"

/*
Type: Item gathering or slaying quest
ID: ID of Item or Enemy required to complete the quest (TODO: Enemy needs ID)
ReqProgress: Count of Items or Enemies required
CurrentProgress: Current Progress

LevelReq: Level required to accept this quest
QuestReq: Quest required to complete before accepting this quest
*/
struct QuestObjective
{
    QuestType Type;
    int ReqProgress;
    int CurrentProgress;
    int ID; 
};

struct Quest
{
    int LevelReq;
    int QuestReq;
    string Name;
    string Text;
    vector<QuestObjective> Objectives;
};

#endif