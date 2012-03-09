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
#include "MapEditor.h"

int main()
{
    sf::RenderWindow MainWindow(sf::VideoMode(1024+((4*32)*2), 768, 32), "Le Window", sf::Style::Close);
    MainWindow.SetFramerateLimit(30);
    MapEditor Editor(MainWindow);

    while(MainWindow.IsOpen()) 
    {
        sf::Event Event;
        while(MainWindow.PollEvent(Event))
        {
            if((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Left))
            {
                sf::IntRect ClickPosition(sf::Mouse::GetPosition(MainWindow).x, sf::Mouse::GetPosition(MainWindow).y, 32, 32);
                if(sf::Mouse::GetPosition(MainWindow).x > 1024)
                    Editor.GrabTile(ClickPosition);
                else
                    Editor.SetTile(ClickPosition);
            }
            else if((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Right))
            {
                sf::IntRect ClickPosition(sf::Mouse::GetPosition(MainWindow).x, sf::Mouse::GetPosition(MainWindow).y, 32, 32);
                if(sf::Mouse::GetPosition(MainWindow).x < 1024)
                    Editor.RemoveObject(ClickPosition);
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Add))
                Editor.ChangeMap(true);
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Subtract))
                Editor.ChangeMap(false);
            else if(Event.Type == sf::Event::Closed)
                MainWindow.Close();
        }
        MainWindow.Clear(sf::Color(128, 128, 128));
        Editor.ShowMap();
        MainWindow.Display();
    }

    Editor.SaveTable(); //le PH

    return 0;
}