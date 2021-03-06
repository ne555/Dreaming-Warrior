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
#include "game.h"

void Game::CopyWorld(const boost::filesystem::path& source, const boost::filesystem::path& dest) 
{
    namespace fs = boost::filesystem;
    try 
    {
        // Check whether the function call is valid
        if(!fs::exists(source) || !fs::is_directory(source)) 
        {
            std::cerr << "Source directory " << source.string().c_str() << " does not exist or is not a directory." << std::endl;
            return;
        }
        if(fs::exists(dest)) 
        {
            cerr << "Destination directory " << dest.string().c_str() << " already exists." << std::endl;
            return;
        }
        // Create the destination directory
        if(!fs::create_directory(dest)) 
        {
            cerr << "Unable to create destination directory " << dest.string().c_str() << std::endl;
            return;
        }
    }
    catch(fs::filesystem_error& e) 
    {
        cerr << e.what() << std::endl;
        return;
    }
    // Iterate through the source directory
    for(fs::directory_iterator it(source); it != fs::directory_iterator(); it++) 
    {
        try 
        {
            fs::path current(it->path());
            if(fs::is_directory(current)) 
            {
                // Found directory: Recursion
                CopyWorld(current, dest.string() + "/" + current.filename().string());
            }
            else 
            {
                // Found file: Copy
                fs::copy_file(current, fs::path(dest.string() + "/" + current.filename().string()));
            }
        }
        catch(fs::filesystem_error& e) 
        {
            cerr << e.what() << std::endl;
        }
    }
}

string RemoveSpaces(string string)
{
    for(auto itr = string.begin(); itr != string.end(); ++itr)
        if(*itr == ' ')
            *itr = '_';
    return string;
}

void Game::SaveMap(string PathToMap)
{
    ofstream File(PathToMap + "Enemies.txt");
    File.clear();
    for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
    {
        File << itr->ID << " " << itr->GetAttack() << " " << itr->GetDefense() 
            << " " << itr->GetHealth() << " " << itr->GetLevel() << " "
            << RemoveSpaces(itr->GetName()) << " " << itr->GetWealth() << " " << itr->GetX() << " "
            << itr->GetY() << " " << itr->MapTextureFileName << " " << itr->Combat << endl;
    }
    File.close();

    File.open(PathToMap + "RandomEncounters.txt");
    File.clear();
    for(auto itr = RandomEncounters.begin(); itr != RandomEncounters.end(); ++itr)
    {
        File << itr->ID << " " << itr->GetAttack() << " " << itr->GetDefense() 
            << " " << itr->GetHealth() << " " << itr->GetLevel() << " "
            << RemoveSpaces(itr->GetName()) << " " << itr->GetWealth() << " " << itr->Combat << endl;
    }
    File.close();

    File.open(PathToMap + "QuestGivers.txt");
    File.clear();
    for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
    {
        File << itr->ID << " " << itr->x << " " << itr->y << " " << itr->TextureFileName << " " << itr->Quests.size();
        for(auto iitr = itr->Quests.begin(); iitr != itr->Quests.end(); ++iitr)
        {
            File << " " << iitr->ID;
        }
        File << endl;
    }
    File.close();
}

void Game::SavePlayer()
{
    ofstream File(World + "/Player.txt");
    File.clear();
    //Basic info
    File << Player.Map << " " << Player.GetX() << " " << Player.GetY() << " " << Player.GetWealth() << " " << RemoveSpaces(Player.GetName()) << " ";
    if(Player.GetClass() == CLASS_WARRIOR)
        File << "0 ";
    else
        File << "1 ";
    //Stats
    File << Player.GetLevel() << " " << Player.GetExp() << " " << Player.GetTalentPoints() << " " << Player.GetIntStr() << " " << Player.GetMaxHealth()
        << " " << Player.GetMaxPower() << " " << Player.GetAttack() << " " << Player.GetDefense() << " " << Player.GetItems().size();
    //Backpack
    for(unsigned i=0; i<Player.GetItems().size(); ++i)
    {
        File << " " << Player.GetItems()[i].ID;
    }
    //Equiped Items
    File << " " << Player.GetEquipedItems().size();
    for(unsigned i=0; i<Player.GetEquipedItems().size(); ++i)
    {
        File << " " << Player.GetEquipedItems()[i].ID;
    }
    //Spells
    File << " " << Player.GetSpells().size();
    for(unsigned i=0; i<Player.GetSpells().size(); ++i)
    {
        File << " " << Player.GetSpells()[i].ID;
    }
    //Quests
    File << " " << Player.GetQuests().size();
    for(unsigned i=0; i<Player.GetQuests().size(); ++i)
    {
        File << " " << Player.GetQuests()[i].ID;
        File << " " << Player.GetQuests()[i].Objective.CurrentProgress;
    }
    //Completed quests
    File << " " << Player.GetCompletedQuests().size();
    for(unsigned i=0; i<Player.GetCompletedQuests().size(); ++i)
    {
        File << " " << Player.GetCompletedQuests()[i];
    }
    File.close();
}