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
#ifndef QUEST_H
#define QUEST_H

#include "Include.h"

/*
Type: Item gathering or slaying quest
ID: ID of Item or Enemy required to complete the quest
ReqProgress: Count of Items or Enemies required
CurrentProgress: Current Progress

LevelReq: Level required to accept this quest
QuestReq: Quest required to complete before accepting this quest
*/
struct QuestObjective
{
    QuestObjective(QuestType Type, int ReqProgress, int ObjectiveID, int CurrentProgress = 0)
        : Type(Type), ReqProgress(ReqProgress), ObjectiveID(ObjectiveID), CurrentProgress(CurrentProgress)
    {
    }
    QuestObjective(QuestType Type, int ReqProgress, int ObjectiveID, string Map, int CurrentProgress = 0)
        : Type(Type), ReqProgress(ReqProgress), ObjectiveID(ObjectiveID), CurrentProgress(CurrentProgress), Map(Map)
    {
    }
    QuestType Type;
    int ReqProgress;
    int CurrentProgress;
    int ObjectiveID;
    string Map; //In case of QuestType == KILL
};

struct Quest
{
    Quest(int ID, string Name, string Text, int LevelReq, int QuestReq, int NumObjectives)
        : ID(ID), Name(Name), Text(Text), LevelReq(LevelReq), QuestReq(QuestReq)
    {
        Objectives.reserve(NumObjectives);
    }
    int ID;
    int LevelReq;
    int QuestReq;
    string Name;
    string Text;
    vector<QuestObjective> Objectives;
};

#endif