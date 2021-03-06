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
#include "combat.h"
#include "game.h"
#include "player.h"

Combat::Combat(sf::RenderWindow &window, Player &player, Enemy enemy) 
    : window(window), player(player), enemy(enemy), TextY(628), ArrowY(165)
{
}

/*
return 0; Game Over
return 1; Win
return 2; Run
*/
int Combat::MainLoop()
{
    sf::Texture ArrowTexture, CombatGUI, CreatureTexture;
    CreatureTexture.loadFromFile(enemy.Combat);
    ArrowTexture.loadFromFile("Graphics/Arrow.png");
    sf::Sprite ArrowSprite(ArrowTexture);
    ArrowSprite.setPosition(800.0f, ArrowY);
    CombatGUI.loadFromFile("Graphics/CombatScreen.jpg");
    Font.loadFromFile("Graphics/papyrus.ttf");
    CreatureSprite.setTexture(CreatureTexture);
    CreatureSprite.setPosition(320.0f, 100.0f);

    sf::Event Event;

    int CommandList = 1;
    int Command = 1;
    bool PlayerMove = true;

    while(window.isOpen()) 
    {
        //Glavni Loop
        while(window.pollEvent(Event))
        {
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(Command != 1)
                {
                    --Command;
                    ArrowY -= 35;
                    ArrowSprite.setPosition(800.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if((Command != 4 && CommandList == 1) || (Command != 3 && CommandList == 2) || (Command != player.GetSpells().size()+1 && CommandList == 3))
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.setPosition(800.0f, ArrowY);
                }
            }
            else if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                if(HandleInput(CommandList, Command, ArrowY, PlayerMove))
                {
                    enemy.SetHealth(enemy.GetHealth());
                    return 2;
                }
                ArrowSprite.setPosition(800.0f, ArrowY);
            }

            // Neprijatelj na potezu
            if(!PlayerMove)
            {
                CreatureAttack();
                PlayerMove = true;
            }

            // Provjeri jel neko mrtav
            if(enemy.GetHealth() <= 0)
            {
                DropLoot();
                player.IncrementExp();
                player.UpdateQuestObjective(enemy.ID);
                return 1;
            }
            else if(player.GetHealth() <= 0)
                return 0;
        }
        // Pokazi sve na ekranu
        window.clear();
        window.draw(sf::Sprite(CombatGUI));
        window.draw(ArrowSprite);
        window.draw(CreatureSprite);
        DrawPlayerStats();
        DrawCommandText(CommandList);
        for(auto itr = CombatTexts.begin(); itr != CombatTexts.end(); ++itr)
            window.draw(*itr);
        window.display();
    }
    return 2;
}

bool Combat::HandleInput(int &CommandList, int &Command, float &ArrowY, bool &PlayerMove)
{
    switch(CommandList)
    {
    case 1: // Glavni Menu
        switch(Command)
        {
        case 1: // Napad
            MeleeAttack();
            PlayerMove = false;
            break;
        case 2: // Magija
            ArrowY = 165.0f;
            Command = 1;
            CommandList = 3;
            break;
        case 3: // Napitak
            ArrowY = 165.0f;
            Command = 1;
            CommandList = 2;
            break;
        case 4: // Bijeg
            if(RunIfCan())
                return true;
            else
                PlayerMove = false;
            break;
        }
        break;
    case 2: // Napitak Menu
        switch(Command)
        {
        case 1: // Health
            player.UseHealthPotIfCan();
            break;
        case 2: // Mana
            player.UsePowerPotIfCan();
            break;
        case 3: // Natrag
            ArrowY = 165.0f;
            Command = 1;
            CommandList = 1;
            break;
        }
        break;
    case 3: // Magija Menu
        if(Command > player.GetSpells().size())
        {
            ArrowY = 165.0f;
            Command = 1;
            CommandList = 1;
            return false;
        }
        SpellCast(player.GetSpells()[Command-1]);
        ArrowY = 165.0f;
        Command = 1;
        CommandList = 1;
        PlayerMove = false;
    }

    return false;
}

void Combat::MeleeAttack()
{
    float Damage;
    switch(player.GetClass())
    {
    case CLASS_WARRIOR:
        Damage = player.GetAttack() + (player.GetIntStr()*3) + urand(0, player.GetLevel()*4) - enemy.GetDefense();
        break;
    case CLASS_MAGE:
        Damage = player.GetAttack();
        break;
    }
    if(Damage < 1)
        Damage = 1;
    enemy.SetHealth(enemy.GetHealth() - Damage);

    // Pokazi text
    string CombatString = player.GetName() + " hits " + enemy.GetName() + " for " + IntToString(Damage) + " damage!";
    HandleCombatText(CombatString);
}

void Combat::CreatureAttack()
{
    // Izracunaj i napravi stetu
    int Damage = urand(enemy.GetAttack(), enemy.GetAttack() + player.GetLevel()) - player.GetDefense();
    if(Damage < 1)
        Damage = 1;
    player.SetHealth(player.GetHealth() - Damage);

    // Pokazi text
    string CombatString = enemy.GetName() + " hits you for " + IntToString(Damage) + " damage!";
    HandleCombatText(CombatString);
}

void Combat::SpellCast(const Spell &Spell)
{
    if(Spell.Cost > player.GetPower())
    {
        switch(player.GetClass())
        {
        case CLASS_WARRIOR:
            HandleCombatText("You failed to cast " + Spell.Name + " due lack of stamina");
            break;
        case CLASS_MAGE:
            HandleCombatText("You failed to cast " + Spell.Name + " due lack of mana!");
            break;
        }
        return;
    }

    int Damage;

    switch(player.GetClass())
    {
    case CLASS_WARRIOR:
        Damage = Spell.Value + player.GetLevel()*2;
        break;
    case CLASS_MAGE:
        Damage = Spell.Value + player.GetIntStr() * 2 + urand(0, player.GetLevel()+2) + player.GetAttack();
        break;
    }

    switch(Spell.Type)
    {
    case SPELL_ATTACK:
        enemy.SetHealth(enemy.GetHealth() - Damage);
        HandleCombatText("Your " + Spell.Name + " hits " + enemy.GetName() + " for " + IntToString(Damage) + " damage!");
        break;
    case SPELL_HEAL:
        player.SetHealth(player.GetHealth() + Damage);
        HandleCombatText("Your " + Spell.Name + " heals you for " + IntToString(Damage) + "!");
        break;
    }
    player.SetPower(player.GetPower() - Spell.Cost);
}

bool Combat::RunIfCan()
{
    if(urand(0, 2) == 0)
    {
        return true;
    }
    else
    {
        HandleCombatText(enemy.GetName() + " gets in your path!");
        return false;
    }
}

void Combat::DropLoot()
{
    player.SetWealth(player.GetWealth() + enemy.GetWealth());
}

void Combat::HandleCombatText(string CombatString)
{
    sf::Text CombatText(CombatString, Font, 25);
    CombatText.setPosition(247.0f, TextY);
    CombatText.setStyle(sf::Text::Bold);
    CombatText.setColor(sf::Color(0, 0, 0));
    CombatTexts.push_back(CombatText);
    TextY += 30;
    if(CombatTexts.size() > 4)
    {
        CombatTexts.erase(CombatTexts.begin());
        for(auto itr = CombatTexts.begin(); itr != CombatTexts.end(); ++itr)
            itr->setPosition(247.0f, itr->getPosition().y - 30.00f);
        TextY -= 30;
    }
}

void Combat::DrawPlayerStats()
{
    sf::Text 
        HealthText("Health: " + IntToString(player.GetHealth()) + "/" + IntToString(player.GetMaxHealth()), Font, 20),
        PowerText("", Font, 20),
        IntStrText("", Font, 20),
        AttackText("Attack: " + IntToString(player.GetAttack()), Font, 20), 
        DefenseText("Defense: " + IntToString(player.GetDefense()), Font, 20);

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

    HealthText.setPosition(20.0f, 205.0f);
    PowerText.setPosition(20.0f, 240.0f);
    AttackText.setPosition(20.0f, 275.0f);
    DefenseText.setPosition(20.0f, 310.0f);
    IntStrText.setPosition(20.0f, 345.0f);

    HealthText.setStyle(sf::Text::Bold);
    PowerText.setStyle(sf::Text::Bold);
    AttackText.setStyle(sf::Text::Bold);
    DefenseText.setStyle(sf::Text::Bold);
    IntStrText.setStyle(sf::Text::Bold);

    window.draw(IntStrText);
    window.draw(HealthText);
    window.draw(PowerText);
    window.draw(AttackText);
    window.draw(DefenseText);
}

void Combat::DrawCommandText(int WhatText)
{
    switch(WhatText)
    {
        case 1:
        {
            sf::Text
                Fight("Attack", Font, 20),
                Spell("Spell", Font, 20),
                Item("Potion", Font, 20),
                Run("Run", Font, 20);

            Fight.setPosition(850, 165);
            Spell.setPosition(850, 200);
            Item.setPosition(850, 235);
            Run.setPosition(850, 270);

            Fight.setStyle(sf::Text::Bold);
            Spell.setStyle(sf::Text::Bold);
            Item.setStyle(sf::Text::Bold);
            Run.setStyle(sf::Text::Bold);

            window.draw(Fight);
            window.draw(Spell);
            window.draw(Item);
            window.draw(Run);
            break;
        }
        case 2:
        {
            sf::Text
                Health("Health (x" + IntToString(player.GetHealthPotNum()) + ")", Font, 20),
                Power("", Font, 20),
                Return("Return ", Font, 20);

            if(player.GetClass() == CLASS_WARRIOR)
                Power.setString("Stamina (x" + IntToString(player.GetPowerPotNum()) + ")");
            else
                Power.setString("Mana: (x" + IntToString(player.GetPowerPotNum()) + ")");

            Health.setPosition(850.0f, 165.0f);
            Power.setPosition(850.0f, 200.0f);
            Return.setPosition(850.0f, 235.0f);

            Health.setStyle(sf::Text::Bold);
            Power.setStyle(sf::Text::Bold);
            Return.setStyle(sf::Text::Bold);

            window.draw(Health);
            window.draw(Power);
            window.draw(Return);
            break;
        }
        case 3:
        {
            float PosY = 165.0f;
            for(auto itr = player.GetSpells().begin(); itr != player.GetSpells().end(); ++itr)
            {
                sf::Text SpellText(itr->Name, Font, 20);
                SpellText.setPosition(850.0f, PosY);
                SpellText.setStyle(sf::Text::Bold);
                window.draw(SpellText);

                PosY += 35;
            }
            sf::Text Return("Return", Font, 20);
            Return.setPosition(850.0f, PosY);
            Return.setStyle(sf::Text::Bold);
            window.draw(Return);
            break;
        }
    }
}