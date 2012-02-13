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
#include "QuestEncounter.h"

QuestEncounter::QuestEncounter(Player &player, sf::RenderWindow &Window)
    : Window(Window), player(player), QuestIterator(0)
{
    sf::Texture ArrowTexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
    ArrowSprite.SetTexture(ArrowTexture);
}

void QuestEncounter::DrawAll()
{
    Window.Clear();
    Window.Draw(ArrowSprite);
}

QuestGiver QuestEncounter::MainLoop(QuestGiver QuestGiver)
{
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
            }
        }
        DrawAll();
        Window.Display();
    }
    return QuestGiver;
}