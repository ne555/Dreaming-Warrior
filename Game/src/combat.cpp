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
    : window(window), player(player), enemy(enemy), TextY(628)
{
}

/*
return 0; Game Over
return 1; Win
return 2; Run
*/
int Combat::MainLoop()
{
    float ArrowY = 60.0f;
    sf::Texture ArrowTexture, CombatGUI, ParchmentTexture;
    ArrowTexture.LoadFromFile("Graphics/Arrow.png");
    sf::Sprite ArrowSprite(ArrowTexture);
    ArrowSprite.SetPosition(800.0f, ArrowY);
    CombatGUI.LoadFromFile("Graphics/CombatScreen.jpg");
    Font.LoadFromFile("Graphics/papyrus.ttf");
    //ParchmentTexture.LoadFromFile("Graphics/Parchment.png");

    sf::Event Event;

    int CommandList = 1;
    int Command = 1;
    bool PlayerMove = true;

    while(window.IsOpen()) 
    {
        //Glavni Loop
        while(window.PollEvent(Event))
        {
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape))
                window.Close();
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Up))
            {
                if(Command != 1)
                {
                    --Command;
                    ArrowY -= 35;
                    ArrowSprite.SetPosition(800.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Down))
            {
                if((Command != 4 && CommandList == 1) || (Command != 3 && CommandList == 2) || (Command != player.GetSpells().size()+1 && CommandList == 3))
                {
                    ++Command;
                    ArrowY += 35;
                    ArrowSprite.SetPosition(800.0f, ArrowY);
                }
            }
            else if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Return))
            {
                if(HandleInput(CommandList, Command, ArrowY, PlayerMove))
                {
                    enemy.SetHealth(enemy.GetHealth());
                    return 2;
                }
                ArrowSprite.SetPosition(800.0f, ArrowY);
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
                enemy.SetHealth(enemy.GetMaxHealth());
                DropLoot(); //PH, implementat
                //dodaj exp, you have reached the level bla bla
                return 1;
            }
            else if(player.GetHealth() <= 0)
                return 0;
        }
        // Pokazi sve na ekranu
        window.Clear();
        //window.Draw(sf::Sprite(ParchmentTexture));
        window.Draw(sf::Sprite(CombatGUI));
        window.Draw(ArrowSprite);
        DrawPlayerStats();
        DrawCommandText(CommandList);
        for(auto itr = CombatTexts.begin(); itr != CombatTexts.end(); ++itr)
            window.Draw(*itr);
        window.Display();
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
            ArrowY = 60.0f;
            Command = 1;
            CommandList = 3;
            break;
        case 3: // Napitak
            ArrowY = 60.0f;
            Command = 1;
            CommandList = 2;
            break;
        case 4: // Bijeg
            if(RunIfCan())
                return true;
            break;
        }
        break;
    case 2: // Napitak Menu
        switch(Command)
        {
        case 1: // Health
            if(player.UseHealthPotIfCan())
                PlayerMove = false;
            break;
        case 2: // Mana
            if(player.UsePowerPotIfCan())
                PlayerMove = false;
            break;
        case 3: // Natrag
            ArrowY = 60.0f;
            Command = 1;
            CommandList = 1;
            break;
        }
        break;
    case 3: // Magija Menu
        if(Command-1 > player.GetSpells().size())
        {
            ArrowY = 60.0f;
            Command = 1;
            CommandList = 1;
            break;
        }
        SpellCast(player.GetSpells()[Command-1]);
        ArrowY = 60.0f;
        Command = 1;
        CommandList = 1;
        PlayerMove = false;
    }

    return false;
}

void Combat::MeleeAttack()
{
    // Izracunaj i napravi stetu
    int Damage = 10;//PH
    enemy.SetHealth(enemy.GetHealth() - Damage);

    // Pokazi text
    string CombatString = player.GetName() + " hits " + enemy.GetName() + " for " + IntToString(Damage) + " damage!";
    HandleCombatText(CombatString);
}

void Combat::CreatureAttack()
{
    // Izracunaj i napravi stetu
    int Damage = 10; //ph
    player.SetHealth(player.GetHealth() - Damage);

    // Pokazi text
    string CombatString = enemy.GetName() + " hits you for " + IntToString(Damage) + " damage!";
    HandleCombatText(CombatString);
}

/*
TODO malo randomiziranja i kalkuliranja da ne bude dosadno
*/
void Combat::SpellCast(const Spell &Spell)
{
    if(Spell.Cost > player.GetPower())
    {
        HandleCombatText("You failed to cast " + Spell.Name + " due lack of mana/power (switch class) [PH]");
        return;
    }

    switch(Spell.Type)
    {
    case SPELL_ATTACK:
        enemy.SetHealth(enemy.GetHealth() - Spell.Value);
        HandleCombatText("Your " + Spell.Name + " hits " + enemy.GetName() + " for " + IntToString(Spell.Value) + " damage!");
        break;
    case SPELL_HEAL:
        player.SetHealth(player.GetHealth() + Spell.Value);
        HandleCombatText("Your " + Spell.Name + " heals you for " + IntToString(Spell.Value) + "!");
        break;
    }
    player.SetPower(player.GetPower() - Spell.Cost);
}

bool Combat::RunIfCan()
{
    //PH
    return true;
}

void Combat::DropLoot()
{
    /*for(auto itr = Enemy->Loot.begin(); itr != Enemy->Loot.end(); ++itr)
    {
        if(urand(0, itr->Chance) == 0)
        {
            Player.SetWealth(Player.GetWealth() + Enemy->GetWealth());
            // Dobio si bla bla golda!
            // Sada pokazi iteme i igrac moze izabrati kojeg oce lootat
            if(!Player.AddItem(itr->Item))
            {
                // TODO: Obavjesti igraca da su mu torbe pune
            }
        }
    }*/
}

void Combat::HandleCombatText(string CombatString)
{
    sf::Text CombatText(CombatString, Font, 25);
    CombatText.SetPosition(247.0f, TextY);
    CombatText.SetStyle(sf::Text::Bold);
    CombatText.SetColor(sf::Color(0, 0, 0));
    CombatTexts.push_back(CombatText);
    TextY += 30;
    if(CombatTexts.size() > 4)
    {
        CombatTexts.erase(CombatTexts.begin());
        for(auto itr = CombatTexts.begin(); itr != CombatTexts.end(); ++itr)
            itr->SetPosition(247.0f, itr->GetPosition().y - 30.00f);
        TextY -= 30;
    }
}

void Combat::DrawPlayerStats()
{
    sf::Text 
        HealthText("Health: " + IntToString(player.GetHealth()) + "/" + IntToString(player.GetMaxHealth()), Font),
        PowerText("", Font),
        IntStrText("", Font),
        AttackText("Attack: " + IntToString(player.GetAttack()), Font), 
        DefenseText("Defense: " + IntToString(player.GetDefense()), Font);

    if(player.GetClass() == CLASS_WARRIOR)
    {
        PowerText.SetString("Stamina: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));
        IntStrText.SetString("Strenght: " + IntToString(player.GetIntStr()));
    }
    else
    {
        PowerText.SetString("Mana: " + IntToString(player.GetPower()) + "/" + IntToString(player.GetMaxPower()));
        IntStrText.SetString("Intelligence: " + IntToString(player.GetIntStr()));
    }

    HealthText.SetPosition(50, 50);
    PowerText.SetPosition(50, 85);
    AttackText.SetPosition(50, 125);
    DefenseText.SetPosition(50, 160);

    window.Draw(HealthText);
    window.Draw(PowerText);
    window.Draw(AttackText);
    window.Draw(DefenseText);
}

void Combat::DrawCommandText(int WhatText)
{
    switch(WhatText)
    {
        case 1:
        {
            sf::Text
                Fight("Attack", Font),
                Spell("Spell", Font),
                Item("Potion", Font),
                Run("Run", Font);

            Fight.SetPosition(850, 60);
            Spell.SetPosition(850, 95);
            Item.SetPosition(850, 130);
            Run.SetPosition(850, 165);

            Fight.SetStyle(sf::Text::Bold);
            Spell.SetStyle(sf::Text::Bold);
            Item.SetStyle(sf::Text::Bold);
            Run.SetStyle(sf::Text::Bold);

            window.Draw(Fight);
            window.Draw(Spell);
            window.Draw(Item);
            window.Draw(Run);
            break;
        }
        case 2:
        {
            /*
            TODO: 
            bice vise imena potova pa kao za spelove
            isto tako promjeni nacin na koji se itemi traze u player class, pa nek se traze osim po tipu i po imenu
            */
            sf::Text
                Health("Health (x" + IntToString(player.GetHealthPotNum()) + ")", Font),
                Power("", Font),
                Return("Return ", Font);

            if(player.GetClass() == CLASS_WARRIOR)
                Power.SetString("Stamina (x" + IntToString(player.GetPowerPotNum()) + ")");
            else
                Power.SetString("Mana: (x" + IntToString(player.GetPowerPotNum()) + ")");

            Health.SetPosition(850.0f, 60.0f);
            Power.SetPosition(850.0f, 95.0f);
            Return.SetPosition(850.0f, 130.0f);
    
            Health.SetColor(sf::Color(255, 255, 255));
            Power.SetColor(sf::Color(255, 255, 255));
            Return.SetColor(sf::Color(255, 255, 255));

            Health.SetStyle(sf::Text::Bold);
            Power.SetStyle(sf::Text::Bold);
            Return.SetStyle(sf::Text::Bold);

            window.Draw(Health);
            window.Draw(Power);
            window.Draw(Return);
            break;
        }
        case 3:
        {
            float PosY = 60.0f;
            for(auto itr = player.GetSpells().begin(); itr != player.GetSpells().end(); ++itr)
            {
                sf::Text SpellText(itr->Name, Font);
                SpellText.SetPosition(850.0f, PosY);
                SpellText.SetStyle(sf::Text::Bold);
                SpellText.SetColor(sf::Color(255, 255, 255));
                window.Draw(SpellText);

                PosY += 35;
            }
            sf::Text Return("Return", Font);
            Return.SetPosition(850.0f, PosY);
            Return.SetStyle(sf::Text::Bold);
            Return.SetColor(sf::Color(255, 255, 255));
            window.Draw(Return);
            break;
        }
    }
}