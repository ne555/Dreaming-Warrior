#include "mainmenu.h"

MainMenu::MainMenu()
{
}

MainMenuData MainMenu::MainLoop()
{
    //PH
    MenuData.World = "DefaultWorld";
    MenuData.PlayerCfgFileName = "";
    return MenuData;
}