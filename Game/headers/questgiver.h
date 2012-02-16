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
#ifndef QGIVER_H
#define QGIVER_H

#include "quest.h"
#include <SFML\Graphics.hpp>

struct QuestGiver
{
    QuestGiver(int ID, int x, int y, string TextureFileName) 
        : ID(ID), x(x), y(y), TextureFileName(TextureFileName)
    {
        MapTexture.LoadFromFile(TextureFileName);
    }

    int ID;
    int x;
    int y;
    sf::Texture MapTexture;
    string TextureFileName;
    vector<Quest> Quests;
};

#endif