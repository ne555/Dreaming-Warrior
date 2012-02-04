#ifndef VENDOR_H
#define VENDOR_H

#include <SFML\Graphics.hpp>
#include "item.h"

struct Vendor
{
    int x;
    int y;
    sf::Texture MapTexture;
    std::vector<Item> Items;
};

#endif