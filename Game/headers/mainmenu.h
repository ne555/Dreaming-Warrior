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
#ifndef MAINMENU_H
#define MAINMENU_H

#include "Include.h"
#include <SFML\Graphics.hpp>

struct MainMenuData
{
    string PathToWorld;
    GameMode Mode;
    Class PlayerClass;
};

class MainMenu
{
    sf::RenderWindow &Window;
    sf::Texture Background;

    GameMode ChooseGameMode();
    Class ChooseClass();

public:
    MainMenu(sf::RenderWindow &Window);
    MainMenuData MainLoop();
};

#endif