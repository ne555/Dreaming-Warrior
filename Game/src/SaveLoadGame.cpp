/*
    This file is part of Game Project.

    Game Project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Game Project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Game Project.  If not, see <http://www.gnu.org/licenses/>.
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
            std::cerr << "Destination directory " << dest.string().c_str() << " already exists." << std::endl;
            return;
        }
        // Create the destination directory
        if(!fs::create_directory(dest)) 
        {
            std::cerr << "Unable to create destination directory " << dest.string().c_str() << std::endl;
            return;
        }
    }
    catch(fs::filesystem_error& e) 
    {
        std::cerr << e.what() << std::endl;
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
            std::cerr << e.what() << std::endl;
        }
    }
}

void Game::SaveMap(string PathToMap)
{
    std::ofstream File(PathToMap + "Enemies.txt");
    File.clear();
    /*
    TODO: Prije nego clearam file ugrabiti file name za odreðene ID enemije
    NPR:
    struct ImageData
    {
        int ID;
        string CombatImageFileName;
        string MapImageFileName;
    };
    vector<ImageData> Foo;
    i onda ih priljepiti dole
    */
    for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
    {
        File << itr->ID << " " << itr->GetAttackPower() << " " << itr->GetArmor() << " "
            << itr->CombatTextureFileName<<  itr->GetLevel() << " "
            << itr->GetName() << " " << itr->GetWealth() << " " << itr->GetX() << " "
            << itr->GetY() << " " << itr->MapTextureFileName;
        int ctr = 4;
        for(auto liter = itr->Loot.begin(); liter != itr->Loot.end(); ++liter)
        {
            File << " " <<liter->Item.ID << " " << liter->Chance;
            --ctr;
        }
        while(ctr > 0)
        {
            File << " NULL 0";
            --ctr;
        }
        File << endl;
    }
    File.close();

    File.open(PathToMap + "Vendors.txt");
    File.clear();
    for(auto itr = Vendors.begin(); itr != Vendors.end(); ++itr)
    {
        File << itr->x << " " << itr->y << " " << itr->TextureFileName << " " << itr->Items.size();
        for(auto iitr = itr->Items.begin(); iitr != itr->Items.end(); ++iitr)
        {
            File << " " << iitr->ID;
        }
        File << endl;
    }
    File.close();

    File.open(PathToMap + "QuestGivers.txt");
    File.clear();
    for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
    {
        File << itr->x << " " << itr->y << " " << itr->TextureFileName << " " << itr->Quests.size();
        for(auto iitr = itr->Quests.begin(); iitr != itr->Quests.end(); ++iitr)
        {
            File << " " << iitr->ID;
        }
        File << endl;
    }
    File.close();

    File.open(World + "/Player.txt");
    File.clear();
    File << Player.GetX() << " " << Player.GetY() << " " << Player.GetName() << " ";
    if(Player.GetClass() == CLASS_WARRIOR)
        File << "0 ";
    else
        File << "1 ";
    File << Player.GetLevel() << " " << Player.GetExp() << " " << Player.GetIntStr() << " " << Player.GetMaxHealth()
        << " " << Player.GetMaxPower() << " " << Player.GetAttackPower() << " " << Player.GetArmor() << endl;
    File.close();
}