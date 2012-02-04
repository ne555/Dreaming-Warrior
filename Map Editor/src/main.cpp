/*
wx widgets
*/
#include "MapEditor.h"

int main()
{
    sf::RenderWindow MainWindow(sf::VideoMode(1024+(4*32), 768, 32), "Le Window", sf::Style::Close);
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