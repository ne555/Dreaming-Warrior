#ifndef QGIVER_H
#define QGIVER_H

#include "quest.h"
#include <SFML\Graphics.hpp>

struct QuestGiver
{
    int x;
    int y;
    sf::Texture MapTexture;
    vector<Quest> Quests;
};

#endif