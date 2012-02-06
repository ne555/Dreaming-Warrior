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