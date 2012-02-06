#ifndef QUEST_ENCOUNTER_H
#define QUEST_ENCOUNTER_H

class Player;

#include "questgiver.h"

class QuestEncounter
{
public:
    QuestEncounter();
    QuestGiver MainLoop(Player &Player, QuestGiver QuestGiver);
};

#endif