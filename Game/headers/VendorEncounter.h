#ifndef VENDOR_ENCOUNTER_H
#define VENDOR_ENCOUNTER_H

#include "vendor.h"

class Player;

class VendorEncounter
{
public:
    VendorEncounter();
    Vendor MainLoop(Player &Player, Vendor Vendor);
};

#endif