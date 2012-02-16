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
/*
TODO: 
- Ne IsSolid, nego object type
*/
#include "game.h"
#include "database.h"

void Game::DrawAll()
{
    Window.Draw(sf::Sprite(MapTexture));
    sf::Sprite PlayerSprite(PlayerTexture);
    PlayerSprite.SetPosition((float)Player.GetX(), (float)Player.GetY());
    Window.Draw(PlayerSprite);

    for(auto itr = Enemies.begin(); itr != Enemies.end(); ++itr)
    {
        sf::Sprite Sprite(itr->CreatureMapTexture);
        Sprite.SetPosition((float)itr->GetX()*32, (float)itr->GetY()*32);
        Window.Draw(Sprite);
    }
    for(auto itr = Vendors.begin(); itr != Vendors.end(); ++itr)
    {
        sf::Sprite Sprite(itr->MapTexture);
        Sprite.SetPosition((float)itr->x*32, (float)itr->y*32);
        Window.Draw(Sprite);
    }
    for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); ++itr)
    {
        sf::Sprite Sprite(itr->MapTexture);
        Sprite.SetPosition((float)itr->x*32, (float)itr->y*32);
        Window.Draw(Sprite);
    }
}

//todo: Pojednostavi.. & loading screen :D
//todo: render texture neradi na svim hardware, mozda capture image i nju load, a ne tile
void Game::LoadMap(string PathToMap)
{
    sf::RenderTexture RenderMapTexture;
    RenderMapTexture.Create(1024, 768);
    this->PathToMap = PathToMap;

    //Unisti staru mapu
    Window.Clear();
    RenderMapTexture.Clear();
    Portals.clear();
    for(int a=0; a<24; ++a)
        for(int b=0; b<32; ++b)
            ObjectGrid[a][b] = NO_OBJECT;

    struct Tile
    {
        Tile(string FileName, bool Solid)
        {
            Texture.LoadFromFile(FileName);
            IsSolid = Solid;
        }
        sf::Texture Texture;
        bool IsSolid;
    };

    int MapTexture[24][32];
    int MapObjects[24][32];
    vector<Tile> Tileset;

    //Ucitaj Teksture
    std::ifstream File(World + "/TekstureBlokovi.txt");
    string ImgFileName;
    bool IsSolid;
    while(File >> ImgFileName >> IsSolid)
    {
        Tileset.push_back(Tile(ImgFileName, IsSolid));
    }
    File.close();

    //Ucitaj Objekte
    File.open(World + "/ObjektBlokovi.txt");
    while(File >> ImgFileName >> IsSolid)
    {
        Tileset.push_back(Tile(ImgFileName, IsSolid));
    }
    File.close();

    //Ucitaj Mapu
    File.open(PathToMap + "MapData.txt");
    for(int y=0; y<24; y++)
    {
        for(int x=0; x<32; x++)
        {
            File >> MapTexture[y][x];
        }
    }
    for(int y=0; y<24; ++y)
    {
        for(int x=0; x<32; ++x)
        {
            File >> MapObjects[y][x];
        }
    }
    File.close();

    //Ucitaj portale
    File.open(PathToMap + "PortalData.txt");
    int x, y, px, py;
    string PathToNewMap;
    while(File >> x >> y >> PathToNewMap >> px >> py)
    {
        Portals.push_back(Portal(x, y, PathToNewMap, px, py));
    }
    File.close();

    //Nacrtaj Mapu i napravi Collision Table
    for(unsigned y = 0; y < 24; ++y) 
    {
        for(unsigned x = 0; x < 32; ++x) 
        {
            if(Tileset[MapTexture[y][x]].IsSolid)
                ObjectGrid[y][x] = SOLID_OBJECT;
            sf::Sprite Texture(Tileset[MapTexture[y][x]].Texture);
            Texture.SetPosition((float)x*32, (float)y*32);
            RenderMapTexture.Draw(Texture);
            if(MapObjects[y][x] == -1)
                continue;
            if(Tileset[MapObjects[y][x]].IsSolid)
                ObjectGrid[y][x] = SOLID_OBJECT;
            sf::Sprite Object(Tileset[MapObjects[y][x]].Texture);
            Object.SetPosition((float)x*32, (float)y*32);
            RenderMapTexture.Draw(Object);
        }
    }

    //Ucitaj cudovista
    int ID, Atk, Def, HP, Level, Wealth;
    int Chance[4];
    string Item[4];
    string CreatureMapTexture, Combat, Name;
    Enemies.clear();
    /*
    TODO: ove iteme na count i for loop a ne vako ruzno
    */
    File.open(PathToMap + "Enemies.txt");
    while(File >> ID >> Atk >> Def >> HP >> Level >> Name >> Wealth >> x >> y >> CreatureMapTexture 
        >> Item[0] >> Chance[0] >> Item[1] >> Chance[1] >> Item[2] >> Chance[2] >> Item[3] >> Chance[3])
    {
        Enemy Enemy(ID, Atk, Def, HP, Level, Name, Wealth, x, y, CreatureMapTexture);
        for(int a = 0; Item[a] != "NULL"; ++a)
            Enemy.Loot.push_back(Loot(GetItemFromDatabase(World, StringToInt(Item[a])), Chance[a]));
        ObjectGrid[y][x] = ENEMY;
        Enemies.push_back(Enemy);
    }
    File.close();

    RandomEncounters.clear();
    File.open(PathToMap + "RandomEncounters.txt");
    while(File >> ID >> Atk >> Def >> HP >> Level >> Name >> Wealth 
        >> Item[0] >> Chance[0] >> Item[1] >> Chance[1] >> Item[2] >> Chance[2] >> Item[3] >> Chance[3])
    {
        Enemy Enemy(ID, Atk, Def, HP, Level, Name, Wealth);
        for(int a = 0; Item[a] != "NULL"; ++a)
            Enemy.Loot.push_back(Loot(GetItemFromDatabase(World, StringToInt(Item[a])), Chance[a]));
        RandomEncounters.push_back(Enemy);
    }
    File.close();
    
    Vendors.clear();
    File.open(PathToMap + "Vendors.txt");
    int Count;
    while(File >> x >> y >> CreatureMapTexture >> Count)
    {
        Vendor Vendor(x, y, CreatureMapTexture);
        for(int i=0; i<Count; ++i)
        {
            int ItemID;
            File >> ItemID;
            Vendor.Items.push_back(GetItemFromDatabase(World, ItemID));
        }
        ObjectGrid[y][x] = VENDOR;
        Vendors.push_back(Vendor);
    }
    File.close();
    
    QuestGivers.clear();
    File.open(PathToMap + "QuestGivers.txt");
    while(File >> ID >> x >> y >> CreatureMapTexture >> Count)
    {
        QuestGiver QuestGiver(ID, x, y, CreatureMapTexture);
        for(int c=0; c<Count; ++c)
        {
            int QuestID;
            File >> QuestID;
            QuestGiver.Quests.push_back(GetQuestFromDatabase(World, QuestID));
        }
        ObjectGrid[y][x] = QUEST;
        QuestGivers.push_back(QuestGiver);
    }
    File.close();

    RenderMapTexture.Display();
    this->MapTexture = RenderMapTexture.GetTexture();
}

bool Game::CheckCollision(int x, int y, Orientation Direction)
{
    switch(Direction)
    {
    case NORTH:
        if(ObjectGrid[y][x] != NO_OBJECT)
            return false;
        break;
    case SOUTH:
        if(ObjectGrid[y][x] != NO_OBJECT)
            return false;
        break;
    case EAST:
        if(ObjectGrid[y][x] != NO_OBJECT)
            return false;
        break;
    case WEST:
        if(ObjectGrid[y][x] != NO_OBJECT)
            return false;
        break;
    }
    return true;
}

bool Game::CheckPortals(int x, int y)
{
    sf::IntRect RectPlayer(x, y, 32, 32);
    for(auto itr = Portals.begin(); itr != Portals.end(); ++itr)
    {
        if(RectPlayer.Intersects(itr->PortalRect))
        {
            //Pokupi vrjednosti prije nego stara mapa bude unistena
            int a = itr->PlayerNewX, b = itr->PlayerNewY;

            //Save mapu
            SaveMap(this->PathToMap);

            //Napravi novu mapu
            LoadMap(World + itr->PathToMap);

            //Relociraj igraca
            Player.SetX(a);
            Player.SetY(b);

            return true;
        }
    }
    return false;
}

bool Game::UpdateMovement(int x, int y, Orientation Direction)
{
    if(!CheckCollision(x/32, y/32, Direction))
        return false;
    sf::Sprite Sprite(PlayerTexture);
    Sprite.SetPosition((float)x, (float)y);
    Window.Draw(Sprite);
    return true;
}