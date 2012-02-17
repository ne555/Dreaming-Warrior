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

Item GetItemFromDatabase(string World, int ID);

/*
TODO: test za completed/progres/nema quest
%C i %N u questovima
to u set spaces staviti

i na desnu stranu knjige REWARDS, PROGRESS
i ako you are not on this quest na input enter aceptat etc etc
*/

QuestEncounter::QuestEncounter(Player &player, sf::RenderWindow &Window)
    : Window(Window), player(player), QuestIterator(0), ArrowY(100.0f)
{
}

bool QuestEncounter::ReadQuestText(QuestGiver &QuestGiver)
{
    sf::Text QuestText(Quests[QuestIterator].Quest.Text);
    QuestText.SetPosition(80.0f, 80.0f);
    sf::Text ObjectiveText
        ("le creature " //TODO ph
        + IntToString(Quests[QuestIterator].Quest.Objectives.begin()->CurrentProgress)//PH
        + "/" + IntToString(Quests[QuestIterator].Quest.Objectives.begin()->ReqProgress)),
        AcceptText(Quests[QuestIterator].From ? "Accept" : "Complete"),
        Decline(Quests[QuestIterator].From ? "Decline" : "Back");
    AcceptText.SetPosition(700.0f, 520.0f);
    Decline.SetPosition(700.0f, 555.0f);
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
                            player.AddItem(GetItemFromDatabase("SavedGame",/*TODO [PH]*/Quests[QuestIterator].Quest.ItemReward));
                            player.RemoveQuest(Quests[QuestIterator].Quest.ID);
                            Quests.erase(Quests.begin() + QuestIterator);
                        }
                        if(Quests.empty())
                            return true;
                    }
                    break;
                case true:
                    return false;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Back))
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

    sf::Texture ArrowTexture, GUITexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
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
                if(ReadQuestText(QuestGiver))
                    return QuestGiver;
                ArrowSprite.SetPosition(555.0f, ArrowY);
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return QuestGiver;
            }
        }
        float QuestNameY = 100.0f;
        Window.Clear();
        Window.Draw(GUISprite);
        for(auto i = Quests.begin(); i != Quests.end(); ++i)
        {
            sf::Text QuestName(i->Quest.Name);
            QuestName.SetPosition(600.0f, QuestNameY);
            QuestNameY += 35;
            Window.Draw(QuestName);
        }
        Window.Draw(ArrowSprite);
        Window.Display();
    }
    return QuestGiver;
}