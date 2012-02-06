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
#ifndef VENDOR_H
#define VENDOR_H

#include <SFML\Graphics.hpp>
#include "item.h"

struct Vendor
{
    Vendor(int x, int y, string TextureFileName) : x(x), y(y)
    {
        MapTexture.LoadFromFile(TextureFileName);
    }
    int x;
    int y;
    sf::Texture MapTexture;
    vector<Item> Items;
};

#endif