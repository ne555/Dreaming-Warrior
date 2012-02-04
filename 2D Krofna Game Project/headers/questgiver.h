#ifndef QGIVER_H
#define QGIVER_H

#include "quest.h"

struct QuestGiver
{
    int x;
    int y;
    sf::Texture MapTexture;
    std::vector<Quest> Quests;
};

#endif