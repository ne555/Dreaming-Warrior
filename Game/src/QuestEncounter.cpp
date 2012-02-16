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
    : Window(Window), player(player), QuestIterator(0), ArrowY(50.0f)
{
}

void QuestEncounter::DrawAll()
{
    float QuestNameY = 50.0f;
    Window.Clear();
    Window.Draw(GUISprite);
    sf::Text QuestText(Quests[QuestIterator].Quest.Text);
    QuestText.SetPosition(150.0f, 100.0f);
    Window.Draw(QuestText);
    sf::Text ObjectiveText
        ("TODO: Ime creature loadat u Quest na pocetku. " 
        + IntToString(Quests[QuestIterator].Quest.Objectives.begin()/*PH*/->CurrentProgress)
        + "/" + IntToString(Quests[QuestIterator].Quest.Objectives.begin()->ReqProgress));
    ObjectiveText.SetPosition(300.0f, 100.0f);
    Window.Draw(ObjectiveText);
    for(auto i = Quests.begin(); i != Quests.end(); ++i)
    {
        sf::Text QuestName(i->Quest.Name);
        QuestName.SetPosition(680, QuestNameY);
        QuestNameY += 35;
        Window.Draw(QuestName);
    }
    Window.Draw(ArrowSprite);
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
    GUITexture.LoadFromFile("Graphics/QuestScreen.png");
    ArrowSprite.SetTexture(ArrowTexture);
    ArrowSprite.SetPosition(645.0f, ArrowY);
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
                    ArrowSprite.SetPosition(645.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(QuestIterator != Quests.size()-1)
                {
                    ++QuestIterator;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(645.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
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
                            break;
                        }
                    }
                    break;
                case false:
                    if(Quests[QuestIterator].Quest.IsComplete())
                    {
                        player.AddCompletedQuest(Quests[QuestIterator].Quest.ID);
                        player.AddItem(GetItemFromDatabase("SavedGame",/*TODO [PH]*/Quests[QuestIterator].Quest.ItemReward));
                        player.RemoveQuest(Quests[QuestIterator].Quest.ID);
                        Quests.erase(Quests.begin() + QuestIterator);
                    }
                    if(Quests.empty())
                        return QuestGiver;
                    break;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return QuestGiver;
            }
        }
        DrawAll();
        Window.Display();
    }
    return QuestGiver;
}