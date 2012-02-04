#ifndef QUEST_H
#define QUEST_H

#include "Include.h"

/*
Type: Item gathering or slaying quest
Objective: Name of Item or Enemy required to complete the quest
ReqProgress: Count of Items or Enemies required
Progress: Current Progress

LevelReq: Level required to accept this quest
QuestReq: Quest required to complete before accepting this quest
*/
struct Quest
{
    Quest(QuestType Type, std::string Objective, int ReqProgress, int Progress, int LevelReq, std::string QuestReq = " ")
        : Type(Type), Objective(Objective), ReqProgress(ReqProgress), Progress(Progress), LevelReq(LevelReq), QuestReq(QuestReq)
    {
    }

    QuestType Type;
    std::string Objective;
    int ReqProgress;
    int Progress;

    int LevelReq;
    std::string QuestReq;
};

#endif