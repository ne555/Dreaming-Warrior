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

struct QuestObjective
{
    QuestObjective()
    {
    }
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
    Quest(int ID, int StartCreature, int EndCreature, string Name, string Text, 
        int LevelReq, int QuestReq, int NumObjectives)
        : ID(ID), StartCreature(StartCreature), EndCreature(EndCreature), Name(Name), 
        Text(Text), LevelReq(LevelReq), QuestReq(QuestReq)
    {
    }
    
    bool IsComplete()
    {
        if(Objective.CurrentProgress < Objective.ReqProgress)
            return false;
        return true;
    }
    int ID;
    int LevelReq;
    int QuestReq;
    int StartCreature;
    int EndCreature;
    int ItemReward;
    string Name;
    string Text;
    QuestObjective Objective;
};

#endif