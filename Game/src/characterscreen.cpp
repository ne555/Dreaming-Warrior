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
#include "QuestScreen.h"
#include "player.h"

CharacterScreen::CharacterScreen(Player &player, sf::RenderWindow &Window)
    : Window(Window), player(player)
{
    ItemName.setPosition(515.0f, 585.0f);
    PointsText.setPosition(480, 55);
    HealthText.setPosition(480, 90);
    PowerText.setPosition(480, 125);
    AttackText.setPosition(480, 160);
    DefenseText.setPosition(480, 195);
    IntStrText.setPosition(480, 230);
    Items.setPosition(890.0f, 580.0f);
    Spells.setPosition(890.0f, 615.0f);
    Stats.setPosition(890.0f, 650.0f);
    Quests.setPosition(890.0f, 685.0f);
    Exit.setPosition(890.0f, 720.0f);

    ItemName.setColor(sf::Color::Black);
    PointsText.setColor(sf::Color::Black);
    HealthText.setColor(sf::Color::Black);
    PowerText.setColor(sf::Color::Black);
    AttackText.setColor(sf::Color::Black);
    DefenseText.setColor(sf::Color::Black);
    IntStrText.setColor(sf::Color::Black);
    Items.setColor(sf::Color::Black);
    Spells.setColor(sf::Color::Black);
    Stats.setColor(sf::Color::Black);
    Quests.setColor(sf::Color::Black);
    Exit.setColor(sf::Color::Black);

    ItemName.setFont(Font);
    PointsText.setFont(Font);
    HealthText.setFont(Font);
    PowerText.setFont(Font);
    AttackText.setFont(Font);
    DefenseText.setFont(Font);
    IntStrText.setFont(Font);
    Items.setFont(Font);
    Spells.setFont(Font);
    Stats.setFont(Font);
    Quests.setFont(Font);
    Exit.setFont(Font);

    ItemName.setStyle(sf::Text::Bold);
    PointsText.setStyle(sf::Text::Bold);
    HealthText.setStyle(sf::Text::Bold);
    PowerText.setStyle(sf::Text::Bold);
    AttackText.setStyle(sf::Text::Bold);
    DefenseText.setStyle(sf::Text::Bold);
    IntStrText.setStyle(sf::Text::Bold);
    Items.setStyle(sf::Text::Bold);
    Spells.setStyle(sf::Text::Bold);
    Stats.setStyle(sf::Text::Bold);
    Quests.setStyle(sf::Text::Bold);
    Exit.setStyle(sf::Text::Bold);

    ItemName.setCharacterSize(20);
    ItemSprite.setPosition(480.0f, 585.0f);
}

void CharacterScreen::ItemsLoop()
{
    unsigned i=0;
    for(int y=0; y<6; ++y)
    {
        for(int x=0; x<5; ++x)
        {
            if(i < player.GetItems().size())
                ItemGrid[y][x] = i;
            else
                ItemGrid[y][x] = -1;
            ++i;
        }
    }
    float ArrowX = 0, ArrowY = 571;
    ArrowSprite.setPosition(ArrowX, ArrowY);
    int IterX = 0, IterY = 0;
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(IterY != 0)
                {
                    IterY -= 1;
                    ArrowY -= 32;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(IterY != 5)
                {
                    IterY += 1;
                    ArrowY += 32;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
            {
                if(IterX != 4)
                {
                    IterX += 1;
                    ArrowX += 79;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
            {
                if(IterX != 0)
                {
                    IterX -= 1;
                    ArrowX -= 79;
                    ArrowSprite.setPosition(ArrowX, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                if(ItemGrid[IterY][IterX] == -1)
                    continue;
                switch(player.GetItems()[ItemGrid[IterY][IterX]].Type)
                {
                case ITEM_QUEST:
                    break;
                case ITEM_POWER_POTION:
                case ITEM_HEALTH_POTION:
                case ITEM_MANA_FOOD:
                    player.SetPower(player.GetPower() + player.GetItems()[ItemGrid[IterY][IterX]].Value);
                    player.RemoveItem(ItemGrid[IterY][IterX]);
                    DrawTexture();
                    break;
                case ITEM_FOOD:
                    player.SetHealth(player.GetHealth() + player.GetItems()[ItemGrid[IterY][IterX]].Value);
                    player.RemoveItem(ItemGrid[IterY][IterX]);
                    DrawTexture();
                    break;
                default:
                    player.EquipItem(player.GetItems()[ItemGrid[IterY][IterX]]);
                    player.RemoveItem(ItemGrid[IterY][IterX]);
                    DrawTexture(); //opet, odvojiti te sheme...
                    break;
                }
                i = 0;
                for(int y=0; y<6; ++y)
                {
                    for(int x=0; x<5; ++x)
                    {
                        if(i < player.GetItems().size())
                            ItemGrid[y][x] = i;
                        else
                            ItemGrid[y][x] = -1;
                     ++i;
                    }
                }
                IterY = IterX = 0;
                ArrowX = 0; ArrowY = 571;
                ArrowSprite.setPosition(0, 571);
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::D))
            {
                if(ItemGrid[IterY][IterX] == -1)
                    continue;
                player.RemoveItem(ItemGrid[IterY][IterX]);
                i = 0;
                for(int y=0; y<6; ++y)
                {
                    for(int x=0; x<5; ++x)
                    {
                        if(i < player.GetItems().size())
                            ItemGrid[y][x] = i;
                        else
                            ItemGrid[y][x] = -1;
                     ++i;
                    }
                }
                IterY = IterX = 0;
                ArrowX = 0; ArrowY = 571;
                ArrowSprite.setPosition(0, 571);
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.clear();
        Window.draw(sf::Sprite(ScreenTexture));
        DrawItems();
        Window.draw(ArrowSprite);
        if(ItemGrid[IterY][IterX] != -1)
        {
            ItemSprite.setTexture(player.GetItems()[ItemGrid[IterY][IterX]].ItemTexture);
            switch(player.GetItems()[ItemGrid[IterY][IterX]].Type) //PH
            {
            case ITEM_FOOD:
                ItemName.setString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_MANA_FOOD:
                ItemName.setString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Cannot be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_POWER_POTION:
                ItemName.setString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " power." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            case ITEM_HEALTH_POTION:
                ItemName.setString
                    (player.GetItems()[ItemGrid[IterY][IterX]].Name 
                    + '\n' + "Regenrates " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].Value)
                    + " health." + '\n' + "Can be used in combat" + '\n'
                    + "Buy Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].BuyPrice) + '\n'
                    + "Sell Price: " + IntToString(player.GetItems()[ItemGrid[IterY][IterX]].SellPrice));
                break;
            }
            Window.draw(ItemName);
            Window.draw(ItemSprite);
        }
        Window.display();
    }
}

inline bool IsHealingSpell(SpellType Type)
{
    switch(Type)
    {
    case SPELL_HEAL:
        return true;
    case SPELL_ATTACK:
        return false;
    }
}

void CharacterScreen::SpellsLoop()
{
    if(player.GetSpells().empty())
        return;
    sf::Texture SpellTexture;
    SpellTexture.loadFromFile("Tiles/Spell.png");
    sf::Sprite SpellSprite(SpellTexture);
    SpellSprite.setPosition(480.0f, 585.0f);

    int Iterator = 0;
    sf::Text SpellText("", Font, 20);
    SpellText.setColor(sf::Color::Black);
    SpellText.setPosition(515.0f, 585.0f);
    SpellText.setStyle(sf::Text::Bold);

    float ArrowY = 50.0f;
    ArrowSprite.setPosition(760.0f, ArrowY);
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(Iterator != 0)
                {
                    --Iterator;
                    ArrowY -= 35;
                    ArrowSprite.setPosition(760.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(Iterator != player.GetSpells().size()-1)
                {
                    ++Iterator;
                    ArrowY += 35;
                    ArrowSprite.setPosition(760.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.clear();
        Window.draw(sf::Sprite(ScreenTexture));
        DrawItems();
        Window.draw(ArrowSprite);
        Window.draw(SpellSprite);
        switch(player.GetSpells()[Iterator].Type)
        {
        case SPELL_HEAL:
            SpellText.setString(player.GetSpells()[Iterator].Name + '\n' +
                "Heals caster for " + IntToString(player.GetSpells()[Iterator].Value) + '\n' +
                "Power Cost: " + IntToString(player.GetSpells()[Iterator].Cost));
            break;
        case SPELL_ATTACK:
            SpellText.setString(player.GetSpells()[Iterator].Name + '\n' +
                "Damages enemy for " + IntToString(player.GetSpells()[Iterator].Value) + '\n' +
                "Power Cost: " + IntToString(player.GetSpells()[Iterator].Cost));
            break;
        }
        Window.draw(SpellText);
        Window.display();
    }
}

void CharacterScreen::StatsLoop()
{
    int Iterator = 0;
    float ArrowY = 95.0f;
    ArrowSprite.setPosition(400.0f, ArrowY);
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(Iterator != 0)
                {
                    --Iterator;
                    ArrowY -= 35;
                    ArrowSprite.setPosition(400.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(Iterator != 4)
                {
                    ++Iterator;
                    ArrowY += 35;
                    ArrowSprite.setPosition(400.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                if(player.GetTalentPoints() < 1)
                    continue;
                //todo [PH]
                switch(Iterator)
                {
                case 0:
                    player.SetMaxHealth(player.GetMaxHealth() + 10);
                    break;
                case 1:
                    player.SetMaxPower(player.GetMaxPower() + 10);
                    break;
                case 2:
                    player.SetAttack(player.GetAttack() + 1);
                    break;
                case 3:
                    player.SetDefense(player.GetDefense() + 1);
                    break;
                case 4:
                    player.SetIntStr(player.GetIntStr() + 1);
                    break;
                }
                player.UseTalentPoint();
                DrawTexture(); //TODO odvojiti stats textove u vise funkcija radi performansa
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
            {
                return;
            }
        }
        Window.clear();
        Window.draw(sf::Sprite(ScreenTexture));
        DrawItems();
        Window.draw(ArrowSprite);
        Window.display();
    }
}

void CharacterScreen::DrawItems()
{
    //Todo equiped items
    float ItemX = 47, ItemY = 571;
    for(auto itr = player.GetItems().begin(); itr != player.GetItems().end(); ++itr)
    {
        sf::Sprite ItemSprite(itr->ItemTexture);
        ItemSprite.setPosition(ItemX, ItemY);
        ItemX += 79;
        if(ItemX == 442)
        {
            ItemY += 32;
            ItemX = 47;
        }
        Window.draw(ItemSprite);
    }
}

void CharacterScreen::DrawTexture()
{
    sf::RenderTexture ScreenTexture;
    ScreenTexture.create(1024, 768);
    //Graphics
    sf::Texture PlayerTexture, BackgroundTexture;
    sf::Text PlayerText("", Font);
    switch(player.GetClass())
    {
    case CLASS_WARRIOR:
        PlayerTexture.loadFromFile("Graphics/Warrior.png");
        PlayerText.setString(player.GetName() + ", level " + IntToString(player.GetLevel()) + " Warrior");
        break;
    case CLASS_MAGE:
        PlayerTexture.loadFromFile("Graphics/Mage.png");
        PlayerText.setString(player.GetName() + ", level " + IntToString(player.GetLevel()) + " Mage");
        break;
    }
    PlayerText.setColor(sf::Color(0, 0, 0));
    PlayerText.setStyle(sf::Text::Bold);
    PlayerText.setPosition(30.0f, 20.0f);
    BackgroundTexture.loadFromFile("Graphics/CharacterScreen.jpg");
    PlayerSprite.setTexture(PlayerTexture);
    PlayerSprite.setPosition(30.0f, 60.0f);
    BackgroundSprite.setTexture(BackgroundTexture);

    ScreenTexture.draw(BackgroundSprite);

    float SpellTextY = 50;
    for(auto itr = player.GetSpells().begin(); itr != player.GetSpells().end(); ++itr)
    {
        sf::Text SpellText(itr->Name, Font);
        SpellText.setPosition(830, SpellTextY);
        SpellText.setColor(sf::Color(0, 0, 0));
        SpellText.setStyle(sf::Text::Bold);
        SpellTextY += 35;
        ScreenTexture.draw(SpellText);
    }

    if(player.GetClass() == CLASS_WARRIOR)
    {
        PowerText.setString("Stamina: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));
        IntStrText.setString("Strenght: " + IntToString(player.GetIntStr()));
    }
    else
    {
        PowerText.setString("Mana: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));
        IntStrText.setString("Intelligence: " + IntToString(player.GetIntStr()));
    }

    PointsText.setString("Points left: " + IntToString(player.GetTalentPoints()));
    HealthText.setString("Health: " + IntToString(player.GetHealth()) + "/" + IntToString(player.GetMaxHealth()));
    AttackText.setString("Attack: " + IntToString(player.GetAttack()));
    DefenseText.setString("Defense: " + IntToString(player.GetDefense()));

    ScreenTexture.draw(PlayerText);
    ScreenTexture.draw(PlayerSprite);
    ScreenTexture.draw(PointsText);
    ScreenTexture.draw(HealthText);
    ScreenTexture.draw(PowerText);
    ScreenTexture.draw(IntStrText);
    ScreenTexture.draw(AttackText);
    ScreenTexture.draw(DefenseText);
    ScreenTexture.draw(Spells);
    ScreenTexture.draw(Stats);
    ScreenTexture.draw(Items);
    ScreenTexture.draw(Quests);
    ScreenTexture.draw(Exit);
    ScreenTexture.display();
    this->ScreenTexture = ScreenTexture.getTexture();
}

void CharacterScreen::MainLoop()
{
    Font.loadFromFile("Graphics/papyrus.ttf");
    sf::Texture ArrowTexture;
    ArrowTexture.loadFromFile("Graphics/Arrow2.png");
    ArrowSprite.setTexture(ArrowTexture);
    ArrowSprite.setPosition(840.0f, 580.0f);
    Items.setString("Items");
    Spells.setString("Spells");
    Stats.setString("Stats");
    Quests.setString("Quests");
    Exit.setString("Exit"),
    DrawTexture();
    int Command = 1;
    float ArrowY = 580.0f;
    while(Window.isOpen()) 
    {
        while(Window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(Command != 1)
                {
                    --Command;
                    ArrowY -= 35;
                    ArrowSprite.setPosition(840.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(Command != 5)
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.setPosition(840.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                switch(Command)
                {
                case 1:
                    ItemsLoop();
                    break;
                case 2:
                    SpellsLoop();
                    break;
                case 3:
                    StatsLoop();
                    break;
                case 4:
                    {
                        if(!player.GetQuests().empty())
                        {
                            QuestScreen QuestScreen(player, Window);
                            QuestScreen.MainLoop();
                        }
                    }
                    break;
                case 5:
                    return;
                }
                ArrowSprite.setPosition(840.0f, ArrowY);
            }
        }
        Window.clear();
        Window.draw(sf::Sprite(ScreenTexture));
        Window.draw(ArrowSprite);
        DrawItems();
        Window.display();
    }
}