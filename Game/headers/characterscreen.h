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
#ifndef CHARACTER_SCREEN_H
#define CHARACTER_SCREEN_H

#include <SFML\Graphics.hpp>
#include "player.h"

class CharacterScreen
{
    sf::RenderWindow &Window;
    sf::Texture ScreenTexture;
    sf::Event Event;
    Player &player;

    sf::Sprite BackgroundSprite;
    sf::Sprite PlayerSprite;
    sf::Sprite ArrowSprite;
    sf::Sprite ItemSprite;

    sf::Text Items, Spells, Stats, Quests, Exit, PointsText, HealthText, 
        PowerText, IntStrText, AttackText, DefenseText, ItemName;

    sf::Font Font;

    int ItemGrid[6][5];

    void DrawTexture();
    void DrawItems();

    void SpellsLoop();
    void ItemsLoop();
    void StatsLoop();
public:
    CharacterScreen(Player &player, sf::RenderWindow &Window);
    void MainLoop();
};

#endif