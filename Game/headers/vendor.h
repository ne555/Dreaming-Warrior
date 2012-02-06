#ifndef VENDOR_H
#define VENDOR_H

#include <SFML\Graphics.hpp>
#include "item.h"

struct Vendor
{
    int x;
    int y;
    sf::Texture MapTexture;
    vector<Item> Items;
};

#endif