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

Item GetItemFromDatabase(const string World, int ID);
string GetEnemyNameFromDatabase(const string Map, int ID);

QuestEncounter::QuestEncounter(Player &player, sf::RenderWindow &Window)
    : Window(Window), player(player), QuestIterator(0), ArrowY(100.0f)
{
}

void QuestEncounter::Victory()
{
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    BackgroundTexture.loadFromFile("Graphics/MainMenu.jpg");
    BackgroundSprite.setTexture(BackgroundTexture);
    sf::Text GameOver("The forest is Saved!", Font, 90U);
    GameOver.setStyle(sf::Text::Bold);
    GameOver.setPosition(230, 320);

    sf::Event Event;
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if(Event.type == sf::Event::KeyPressed)
            {
                exit(0);
            }
        }
        Window.clear();
        Window.draw(BackgroundSprite);
        Window.draw(GameOver);
        Window.display();
    }
}

bool QuestEncounter::ReadQuestText(QuestGiver &QuestGiver)
{
    sf::Text QuestText(Quests[QuestIterator].Quest.Text, Font);
    QuestText.setPosition(40.0f, 40.0f);
    QuestText.setColor(sf::Color(0, 0, 0));
    QuestText.setStyle(sf::Text::Bold);
    sf::Text ObjectiveText
        (GetEnemyNameFromDatabase("World" + Quests[QuestIterator].Quest.Objective.Map, Quests[QuestIterator].Quest.Objective.ObjectiveID) + " " //TODO PH LOL KOJA INDIREKCIJA
        + IntToString(Quests[QuestIterator].Quest.Objective.CurrentProgress)
        + "/" + IntToString(Quests[QuestIterator].Quest.Objective.ReqProgress), Font),
        AcceptText(Quests[QuestIterator].From ? "Accept" : "Complete", Font),
        Decline(Quests[QuestIterator].From ? "Decline" : "Back", Font);
    AcceptText.setPosition(700.0f, 520.0f);
    ObjectiveText.setColor(sf::Color(0, 0, 0));
    Decline.setPosition(700.0f, 555.0f);
    AcceptText.setColor(sf::Color(0, 0, 0));
    Decline.setColor(sf::Color(0, 0, 0));
    ObjectiveText.setPosition(580.0f, 90.0f);
    ArrowSprite.setPosition(660.0f, 520.0f);

    bool Accept = false;
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(Accept)
                {
                    Accept = false;
                    ArrowSprite.setPosition(660.0f, 520.0f);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(!Accept)
                {
                    Accept = true;
                    ArrowSprite.setPosition(660.0f, 555.0f);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                switch(Accept)
                {
                case false:
                    switch(Quests[QuestIterator].From)
                    {
                    case true:
                        player.AddQuest(Quests[QuestIterator].Quest);
                        Quests[QuestIterator].From = false;
                        for(auto itr = QuestGiver.Quests.begin(); itr != QuestGiver.Quests.end(); ++itr)
                        {
                            if(itr->ID == Quests[QuestIterator].Quest.ID)
                            {
                                QuestGiver.Quests.erase(itr);
                                return false;
                            }
                        }
                    case false:
                        if(Quests[QuestIterator].Quest.IsComplete())
                        {
                            player.AddCompletedQuest(Quests[QuestIterator].Quest.ID);
                            player.AddItem(GetItemFromDatabase("SavedGame", Quests[QuestIterator].Quest.ItemReward));
                            player.RemoveQuest(Quests[QuestIterator].Quest.ID);
                            if(Quests[QuestIterator].Quest.ID == 10)
                                Victory();
                            Quests.erase(Quests.begin() + QuestIterator);
                            player.SetWealth(player.GetWealth() + 20 * player.GetLevel());
                        }
                        if(Quests.empty())
                            return true;
                    }
                    break;
                case true:
                    return false;
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
            {
                return false;
            }
        }
        Window.clear();
        Window.draw(GUISprite);
        Window.draw(ArrowSprite);
        Window.draw(AcceptText);
        Window.draw(Decline);
        Window.draw(ObjectiveText);
        Window.draw(QuestText);
        Window.display();
    }
    return false;
}

QuestGiver QuestEncounter::MainLoop(QuestGiver QuestGiver)
{
    for(auto i = QuestGiver.Quests.begin(); i != QuestGiver.Quests.end(); ++i)
    {
        //Ovaj check je upitan...
        if(player.GetLevel() < i->LevelReq || (!player.HasCompletedQuest(i->QuestReq) && i->QuestReq != -1))
            continue;
        Quests.push_back(_Quest(*i, true));
    }
    for(auto i = player.GetQuests().begin(); i != player.GetQuests().end(); ++i)
    {
        if(i->EndCreature == QuestGiver.ID)
        {
            Quests.push_back(_Quest(*i, false));
        }
    }
    if(Quests.empty())
        return QuestGiver;

    Font.loadFromFile("Graphics/papyrus.ttf");

    sf::Texture ArrowTexture, GUITexture;
    ArrowTexture.loadFromFile("Graphics/Arrow2.png");
    GUITexture.loadFromFile("Graphics/QuestScreen.jpg");
    ArrowSprite.setTexture(ArrowTexture);
    ArrowSprite.setPosition(555.0f, ArrowY);
    GUISprite.setTexture(GUITexture);

    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(QuestIterator != 0)
                {
                    --QuestIterator;
                    ArrowY -= 35;
                    ArrowSprite.setPosition(555.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(QuestIterator != Quests.size()-1)
                {
                    ++QuestIterator;
                    ArrowY += 35;
                    ArrowSprite.setPosition(555.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                if(ReadQuestText(QuestGiver))
                    return QuestGiver;
                ArrowSprite.setPosition(555.0f, ArrowY);
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
            {
                return QuestGiver;
            }
        }
        float QuestNameY = 100.0f;
        Window.clear();
        Window.draw(GUISprite);
        for(auto i = Quests.begin(); i != Quests.end(); ++i)
        {
            sf::Text QuestName(i->Quest.Name, Font);
            QuestName.setPosition(600.0f, QuestNameY);
            QuestName.setColor(sf::Color(0, 0, 0));
            QuestNameY += 35;
            Window.draw(QuestName);
        }
        Window.draw(ArrowSprite);
        Window.display();
    }
    return QuestGiver;
}