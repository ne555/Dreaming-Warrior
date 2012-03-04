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

QuestEncounter::QuestEncounter(Player &player, sf::RenderWindow &Window, QuestGiver questGiver)
    : Window(Window), player(player), questGiver(questGiver), QuestIterator(0), ArrowY(100.0f)
{
}

void QuestEncounter::Victory()
{
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    BackgroundTexture.LoadFromFile("Graphics/MainMenu.jpg");
    BackgroundSprite.SetTexture(BackgroundTexture);
    sf::Text GameOver("The forest is Saved!", Font, 90U);
    GameOver.SetStyle(sf::Text::Bold);
    GameOver.SetPosition(230, 320);

    sf::Event Event;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if(Event.Type == sf::Event::KeyPressed)
            {
                exit(0);
            }
        }
        Window.Clear();
        Window.Draw(BackgroundSprite);
        Window.Draw(GameOver);
        Window.Display();
    }
}

bool QuestEncounter::ReadQuestText()
{
    sf::Text QuestText(Quests[QuestIterator].Quest.Text, Font);
    QuestText.SetPosition(40.0f, 40.0f);
    QuestText.SetColor(sf::Color(0, 0, 0));
    QuestText.SetStyle(sf::Text::Bold);
    sf::Text ObjectiveText
        (GetEnemyNameFromDatabase("World" + Quests[QuestIterator].Quest.Objective.Map, Quests[QuestIterator].Quest.Objective.ObjectiveID) + " " //TODO PH LOL KOJA INDIREKCIJA
        + IntToString(Quests[QuestIterator].Quest.Objective.CurrentProgress)//PH
        + "/" + IntToString(Quests[QuestIterator].Quest.Objective.ReqProgress), Font),
        AcceptText(Quests[QuestIterator].From ? "Accept" : "Complete", Font),
        Decline(Quests[QuestIterator].From ? "Decline" : "Back", Font);
    AcceptText.SetPosition(700.0f, 520.0f);
    ObjectiveText.SetColor(sf::Color(0, 0, 0));
    Decline.SetPosition(700.0f, 555.0f);
    AcceptText.SetColor(sf::Color(0, 0, 0));
    Decline.SetColor(sf::Color(0, 0, 0));
    ObjectiveText.SetPosition(580.0f, 90.0f);
    ArrowSprite.SetPosition(660.0f, 520.0f);

    bool Accept = false;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(Accept)
                {
                    Accept = false;
                    ArrowSprite.SetPosition(660.0f, 520.0f);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(!Accept)
                {
                    Accept = true;
                    ArrowSprite.SetPosition(660.0f, 555.0f);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(Accept)
                {
                case false:
                    switch(Quests[QuestIterator].From)
                    {
                    case true:
                        player.AddQuest(Quests[QuestIterator].Quest);
                        Quests[QuestIterator].From = false;
                        for(auto itr = questGiver.Quests.begin(); itr != questGiver.Quests.end(); ++itr)
                        {
                            if(itr->ID == Quests[QuestIterator].Quest.ID)
                            {
                                questGiver.Quests.erase(itr);
                                return false;
                            }
                        }
                    case false:
                        if(Quests[QuestIterator].Quest.IsComplete())
                        {
                            player.AddCompletedQuest(Quests[QuestIterator].Quest.ID);
                            player.AddItem(GetItemFromDatabase("SavedGame",Quests[QuestIterator].Quest.ItemReward));
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
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return false;
            }
        }
        Window.Clear();
        Window.Draw(GUISprite);
        Window.Draw(ArrowSprite);
        Window.Draw(AcceptText);
        Window.Draw(Decline);
        Window.Draw(ObjectiveText);
        Window.Draw(QuestText);
        Window.Display();
    }
    return false;
}

void QuestEncounter::MainLoop()
{
    for(auto i = questGiver.Quests.begin(); i != questGiver.Quests.end(); ++i)
    {
        //Ovaj check je upitan...
        if(player.GetLevel() < i->LevelReq || (!player.HasCompletedQuest(i->QuestReq) && i->QuestReq != -1))
            continue;
        Quests.push_back(_Quest(*i, true));
    }
    for(auto i = player.GetQuests().begin(); i != player.GetQuests().end(); ++i)
    {
        if(i->EndCreature == questGiver.ID)
        {
            Quests.push_back(_Quest(*i, false));
        }
    }
    if(Quests.empty())
        return;

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
                if(QuestIterator != Quests.size()-1)
                {
                    ++QuestIterator;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(555.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                if(ReadQuestText())
                    return;
                ArrowSprite.SetPosition(555.0f, ArrowY);
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        float QuestNameY = 100.0f;
        Window.Clear();
        Window.Draw(GUISprite);
        for(auto i = Quests.begin(); i != Quests.end(); ++i)
        {
            sf::Text QuestName(i->Quest.Name, Font);
            QuestName.SetPosition(600.0f, QuestNameY);
            QuestName.SetColor(sf::Color(0, 0, 0));
            QuestNameY += 35;
            Window.Draw(QuestName);
        }
        Window.Draw(ArrowSprite);
        Window.Display();
    }
}