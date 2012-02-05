#include "game.h"

Item GetItemFromDatabase(int ID);
Quest GetQuestFromDatabase(int ID);

//todo: Pojednostavi.. & loading screen :D
//todo: render texture neradi na svim hardware, mozda capture image i nju load, a ne tile
void Game::LoadMap(std::string PathToMap)
{
    sf::RenderTexture RenderMapTexture;
    RenderMapTexture.Create(1024, 768);

    //Unisti staru mapu
    Window.Clear();
    RenderMapTexture.Clear();
    Portals.clear();
    for(int a=0; a<24; a++)
        for(int b=0; b<32; b++)
            CreatureGrid[a][b] = NO_CREATURE;

    struct Tile
    {
        Tile(std::string FileName, bool Solid)
        {
            Texture.LoadFromFile(FileName);
            IsSolid = Solid;
        }
        sf::Texture Texture;
        bool IsSolid;
    };

    int MapTexture[24][32];
    int MapObjects[24][32];
    std::vector<Tile> Tileset;

    //Ucitaj Teksture
    std::ifstream File(World + "/TekstureBlokovi.txt");
    std::string ImgFileName;
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
    for(int y=0; y<24; y++)
    {
        for(int x=0; x<32; x++)
        {
            File >> MapObjects[y][x];
        }
    }
    File.close();

    //Ucitaj portale
    File.open(PathToMap + "PortalData.txt");
    int x, y, px, py;
    std::string PathToNewMap;
    while(File >> x >> y >> PathToNewMap >> px >> py)
    {
        Portals.push_back(Portal(x, y, PathToNewMap, px, py));
    }
    File.close();

    //Nacrtaj Mapu i napravi Collision Table
    for(unsigned y = 0; y < 24; y++) 
    {
        for(unsigned x = 0; x < 32; x++) 
        {
            CollisionGrid[y][x] = Tileset[MapTexture[y][x]].IsSolid;
            sf::Sprite Texture(Tileset[MapTexture[y][x]].Texture);
            Texture.SetPosition((float)x*32, (float)y*32);
            RenderMapTexture.Draw(Texture);
            if(MapObjects[y][x] == -1)
                continue;
            CollisionGrid[y][x] = Tileset[MapObjects[y][x]].IsSolid;
            sf::Sprite Object(Tileset[MapObjects[y][x]].Texture);
            Object.SetPosition((float)x*32, (float)y*32);
            RenderMapTexture.Draw(Object);
        }
    }

    PlayerTexture = Tileset[0].Texture;

    //Ucitaj cudovista
    int Atk, Def, HP, Level;
    std::string CreatureMapTexture, Combat, Name;

    Enemies.clear();
    File.open(PathToMap + "Enemies.txt");
    while(File >> Atk >> Def >> HP >> x >> y >> CreatureMapTexture >> Combat >> Level >> Name)
    {
        Enemies.push_back(Enemy(Atk, Def, HP, x, y, CreatureMapTexture, Combat, Level, Name));
    }
    File.close();

    RandomEncounters.clear();
    File.open(PathToMap + "RandomEncounters.txt");
    while(File >> Atk >> Def >> HP >> Combat >> Level >> Name)
    {
        RandomEncounters.push_back(Enemy(Atk, Def, HP, Combat, Level, Name));
    }
    File.close();

    Vendors.clear();
    File.open(PathToMap + "Vendors.txt");
    std::string line, buffer;
    int a = 0, c = 0;
    Vendor Vendor;
    while(getline(File, line))
    {
        while(a != line.size())
        {
            while(line[a] != ' ')
            {
                buffer = line[a];
                a++;
            }
            switch(c)
            {
            case 0:
                Vendor.x = StringToInt(buffer);
                break;
            case 1:
                Vendor.y = StringToInt(buffer);
                break;
            case 2:
                Vendor.MapTexture.LoadFromFile(buffer);
                break;
            default:
                Vendor.Items.push_back(GetItemFromDatabase(StringToInt(buffer)));
            }
            a++; c++;
            buffer.clear();
        }
        Vendors.push_back(Vendor);
    }
    File.close();

    QuestGivers.clear();
    File.open(PathToMap + "QuestGivers.txt");
    a = 0; c = 0;
    QuestGiver QuestGiver;
    while(getline(File, line))
    {
        while(a != line.size())
        {
            while(line[a] != ' ')
            {
                buffer = line[a];
                a++;
            }
            switch(c)
            {
            case 0:
                QuestGiver.x = StringToInt(buffer);
                break;
            case 1:
                QuestGiver.y = StringToInt(buffer);
                break;
            case 2:
                QuestGiver.MapTexture.LoadFromFile(buffer);
                break;
            default:
                QuestGiver.Quests.push_back(GetQuestFromDatabase(StringToInt(buffer)));
            }
            a++; c++;
            buffer.clear();
        }
        Vendors.push_back(Vendor);
    }
    File.close();

    for(auto itr = Enemies.begin(); itr != Enemies.end(); itr++)
    {
        CreatureGrid[itr->GetY()][itr->GetX()] = ENEMY;
    }
    for(auto itr = Vendors.begin(); itr != Vendors.end(); itr++)
    {
        CreatureGrid[itr->y][itr->x] = VENDOR;
    }
    for(auto itr = QuestGivers.begin(); itr != QuestGivers.end(); itr++)
    {
        CreatureGrid[itr->y][itr->x] = ENEMY;
    }

    RenderMapTexture.Display();
    this->MapTexture = RenderMapTexture.GetTexture();
}

bool Game::CheckCollision(int x, int y, Orientation Direction)
{
    switch(Direction)
    {
    case NORTH:
        if(CollisionGrid[y][x])
            return false;
        break;
    case SOUTH:
        if(CollisionGrid[y][x])
            return false;
        break;
    case EAST:
        if(CollisionGrid[y][x])
            return false;
        break;
    case WEST:
        if(CollisionGrid[y][x])
            return false;
        break;
    }
    return true;
}

bool Game::CheckPortals(int x, int y)
{
    sf::IntRect RectPlayer(x, y, 32, 32);
    for(auto itr = Portals.begin(); itr != Portals.end(); itr++)
    {
        if(RectPlayer.Intersects(itr->PortalRect))
        {
            //Pokupi vrjednosti prije nego stara mapa bude unistena
            int a = itr->PlayerNewX, b = itr->PlayerNewY;
            std::string Path = itr->PathToMap;

            //Napravi novu mapu
            LoadMap(itr->PathToMap);

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