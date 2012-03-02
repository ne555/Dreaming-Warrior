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

#include "QuestScreen.h"

string GetEnemyNameFromDatabase(string, int);

QuestScreen::QuestScreen(Player &player, sf::RenderWindow &Window)
    : player(player), Window(Window), ArrowY(100.0f), QuestIterator(0)
{
}

void QuestScreen::ReadQuestText()
{
    sf::Text QuestText(player.GetQuests()[QuestIterator].Text, Font);
    QuestText.SetPosition(40.0f, 40.0f);
    QuestText.SetColor(sf::Color(0, 0, 0));
    sf::Text ObjectiveText
        (GetEnemyNameFromDatabase("World" + player.GetQuests()[QuestIterator].Objective.Map, player.GetQuests()[QuestIterator].Objective.ObjectiveID) + " " //TODO ph
        + IntToString(player.GetQuests()[QuestIterator].Objective.CurrentProgress)//PH
        + "/" + IntToString(player.GetQuests()[QuestIterator].Objective.ReqProgress), Font);
    ObjectiveText.SetPosition(580.0f, 90.0f);
    ObjectiveText.SetColor(sf::Color(0, 0, 0));

    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.Clear();
        Window.Draw(GUISprite);
        Window.Draw(ObjectiveText);
        Window.Draw(QuestText);
        Window.Display();
    }
    return;
}

void QuestScreen::MainLoop()
{
    Font.LoadFromFile("Graphics/papyrus.ttf");
    sf::Texture ArrowTexture, GUITexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow2.png");
    GUITexture.LoadFromFile("Graphics/QuestScreen.jpg");
    ArrowSprite.SetTexture(ArrowTexture);
    ArrowSprite.SetPosition(555.0f, ArrowY);
    GUISprite.SetTexture(GUITexture);

    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(QuestIterator != 0)
                {
                    --QuestIterator;
                    ArrowY -= 35;
                    ArrowSprite.SetPosition(555.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(QuestIterator != player.GetQuests().size())
                {
                    ++QuestIterator;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(555.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                ReadQuestText();
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        float QuestNameY = 100.0f;
        Window.Clear();
        Window.Draw(GUISprite);
        for(auto i = player.GetQuests().begin(); i != player.GetQuests().end(); ++i)
        {
            sf::Text QuestName(i->Name, Font);
            QuestName.SetPosition(600.0f, QuestNameY);
            QuestName.SetColor(sf::Color(0, 0, 0));
            QuestNameY += 35;
            Window.Draw(QuestName);
        }
        Window.Draw(ArrowSprite);
        Window.Display();
    }
}