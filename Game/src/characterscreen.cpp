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
#include "characterscreen.h"
#include "player.h"

/*
TODO: Pokazi lika, equipane iteme, questove i statse
i ovo class jer treba swap izmeðu questova

TODO: Pokazi lika, backpack iteme, omoguci mjenjanje statsa, omoguci mjenjanje equipa

Ostavi mjesta meðu itemima za strelicu koja je 32x32
*/

CharacterScreen::CharacterScreen(Player &player, sf::RenderWindow &Window)
    : Window(Window), player(player), QuestIterator(0)
{
    sf::Texture PlayerTexture, ArrowTexture, BackgroundTexture;
    switch(player.GetClass())
    {
    case CLASS_WARRIOR:
        PlayerTexture.LoadFromFile("Graphics/Warrior.png");
        break;
    case CLASS_MAGE:
        PlayerTexture.LoadFromFile("Graphics/Mage.png");
        break;
    }
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
    BackgroundTexture.LoadFromFile("Graphics/CharacterScreen.png");
    ArrowSprite.SetTexture(ArrowTexture);
    PlayerSprite.SetTexture(PlayerTexture);
    BackgroundSprite.SetTexture(BackgroundTexture);
}

void CharacterScreen::DrawAll()
{
    Window.Clear();
    Window.Draw(BackgroundSprite);
    sf::Text QuestText(player.GetQuests()[QuestIterator].Text);
    //QuestText.SetPosition();
    float QuestNameY; //TODO = gdje je sad
    for(int i=0; i<player.GetQuests().size(); ++i)
    {
        sf::Text QuestName(player.GetQuests()[i].Name);
        //QuestName.SetPosition(, QuestNameY);
        Window.Draw(QuestName);
    }
    for(int i=0; i<player.GetEquipedItems().size(); ++i)
    {
        sf::Sprite ItemSprite(player.GetItems()[i].Visual);
        switch(player.GetItems()[i].Type)
        {
        case ITEM_HEAD:
            //ItemSprite.SetPosition();
            break;
        case ITEM_CHEST:
            //ItemSprite.SetPosition();
            break;
        case ITEM_HANDS:
            //ItemSprite.SetPosition();
            break;
        case ITEM_LEGS:
            //ItemSprite.SetPosition();
            break;
        case ITEM_FOOT:
            //ItemSprite.SetPosition();
            break;
        case ITEM_WEAPON:
            //ItemSprite.SetPosition();
            break;
        }
        Window.Draw(ItemSprite);
    }
    //TODO: i itemi iz torbice
    //Window.Draw(QuestText);
    Window.Draw(PlayerSprite);
    Window.Draw(ArrowSprite);
}

void CharacterScreen::ItemsLoop()
{
}

void CharacterScreen::QuestsLoop()
{
    if(player.GetQuests().size() == 0)
        return;
    int QItr = 1;
    float ArrowY; //TODO = 
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Left))
            {
                if(QItr != 1)
                {
                    --QItr;
                    //ArrowSprite.SetPosition(, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Right))
            {
                if(QItr != player.GetQuests().size())
                {
                    ++QItr;
                    //ArrowSprite.SetPosition(, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                QuestIterator = QItr;
                return;
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        DrawAll();
        Window.Display();
    }
}

void CharacterScreen::MainLoop()
{
    int Command = 1;
    while(Window.IsOpen()) 
    {
        while(Window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(Command != 1)
                {
                    --Command;
                    //ArrowSprite.SetPosition();
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if(Command != 2)
                {
                    ++Command;
                    //ArrowSprite.SetPosition();
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                switch(Command)
                {
                case 1:
                    QuestsLoop();
                    break;
                case 2:
                    ItemsLoop();
                    break;
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        DrawAll();
        Window.Display();
    }
}