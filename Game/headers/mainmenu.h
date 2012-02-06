#ifndef MAINMENU_H
#define MAINMENU_H

#include "Include.h"

struct MainMenuData
{
    //todo: start map std:.string
    string PlayerCfgFileName;
    string World; // Default ili Custom TODO: mozda da enable kolko god svjetova postoji da se loaduju
    MainMenuResult Result;
};

class MainMenu
{
    MainMenuData MenuData;

public:
    MainMenu();
    MainMenuData MainLoop();
};

#endif