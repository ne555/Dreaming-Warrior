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
#ifndef QUEST_ENCOUNTER_H
#define QUEST_ENCOUNTER_H

#include "player.h"
#include "questgiver.h"

class QuestEncounter
{
    sf::RenderWindow &Window;
    sf::Event Event;
    sf::Sprite ArrowSprite;
    sf::Sprite GUISprite;
    sf::Font Font;
    Player &player;

    struct _Quest
    {
        _Quest(Quest Quest, bool From)
            : Quest(Quest), From(From)
        {
        }
        Quest Quest;
        //false - Player
        //true - QGiver
        bool From;
    };

    vector<_Quest> Quests;
    int QuestIterator;
    float ArrowY;

    bool ReadQuestText(QuestGiver &QuestGiver);

public:
    QuestEncounter(Player &player, sf::RenderWindow &Window);
    QuestGiver MainLoop(QuestGiver QuestGiver);
};

#endif