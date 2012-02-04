#include "MapEditor.h"

MapEditor::MapEditor(sf::RenderWindow &Window)
{
    MapWindow = &Window;
    CurrentMapId = 1;
    std::stringstream convert;
    convert << CurrentMapId;
    PathToCurrentMap = "CustomWorld/Map" + convert.str() + "/";
    MapWindow->SetTitle(PathToCurrentMap + "MapData.txt");
    TrenutniTile = 1;
	for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            RectTable[y][x].Height = 32;
            RectTable[y][x].Width = 32;
            RectTable[y][x].Left = 32*x;
            RectTable[y][x].Top = 32*y;
        }
    }
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            ObjectTable[y][x] = -1;
        }
    }
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            TextureTable[y][x] = 1;
        }
    }
    LoadTileset();
    LoadTable();//PH
}

void MapEditor::LoadTable()
{
    std::ifstream File(PathToCurrentMap + "MapData.txt");
    if(!File.is_open())
        return;

    for(int y=0; y<24; y++)
    {
        for(int x=0; x<32; x++)
        {
            File >> TextureTable[y][x];
        }
    }
    for(int y=0; y<24; y++)
    {
        for(int x=0; x<32; x++)
        {
            File >>ObjectTable[y][x];
        }
    }
    File.close();
}

void MapEditor::LoadTileset()
{
    std::ifstream File("CustomWorld/TekstureBlokovi.txt");
    BrojTiles = 0;
    std::string ImgFileName;
    int x = 0, y = 0;
    bool IsSolid;
    while(File >> ImgFileName >> IsSolid)
    {
        sf::Texture Texture;
        Texture.LoadFromFile(ImgFileName);
        Tileset.push_back(new Tile(Texture, false));
        TilesetRectTable[y][x].Height = 32;
        TilesetRectTable[y][x].Width = 32;
        TilesetRectTable[y][x].Left = 1024+(32*x);
        TilesetRectTable[y][x].Top = 32*y;
        TilesetTable[y][x] = BrojTiles;
        x++;
        if(x==4)
        {
            x = 0;
            y++;
        }
        BrojTiles++;
    }
    /*
    TODO:
    S jedne strane teksture, s druge objekti!!
    Znaci 2 tileset table
    baci error ako ih bude previse
    TODO: 40*32 + 40*32 px strelica za sljedecu i proslu stranicu tileseta
    */
    File.close();
    File.open("CustomWorld/ObjektBlokovi.txt");
    while(File >> ImgFileName >> IsSolid)
    {
        if(BrojTiles == 4*24)//PH, obrisat limit
            break;
        sf::Texture Texture;
        Texture.LoadFromFile(ImgFileName);
        Tileset.push_back(new Tile(Texture, true));
        TilesetRectTable[y][x].Height = 32;
        TilesetRectTable[y][x].Width = 32;
        TilesetRectTable[y][x].Left = 1024+(32*x);
        TilesetRectTable[y][x].Top = 32*y;
        TilesetTable[y][x] = BrojTiles;
        x++;
        if(x==4)
        {
            x = 0;
            y++;
        }
        BrojTiles++;
    }
}

void MapEditor::ShowMap()
{
    for(int y = 0; y < 24; y++) 
    {
        for(int x = 0; x < 32; x++) 
        {
            sf::Sprite Sprite;
            Sprite.SetTexture(Tileset[TextureTable[y][x]]->Texture);
            Sprite.SetPosition(x*32, y*32);
            MapWindow->Draw(Sprite);
            if(ObjectTable[y][x] == -1)
                continue;
            Sprite.SetTexture(Tileset[ObjectTable[y][x]]->Texture);
            Sprite.SetPosition(x*32, y*32);
            MapWindow->Draw(Sprite);
        }
    }

    std::vector<Tile*>::iterator iter = Tileset.begin();

    /*
    TODO: objekti na jednu stranu texture na drugu
    */
    for(int a=0; a<24; a++)//PH! limit obrisat
    {
        for(int b=0; b<4; b++)
        {
            if(iter == Tileset.end())
                goto izlaz;
            sf::Sprite Sprite;
            Sprite.SetTexture((*iter)->Texture);
            Sprite.SetPosition(1024+(b*32), a*32);
            MapWindow->Draw(Sprite);
            iter++;
        }
    }
    izlaz:

    for(int a=32; a<1152; a+=32)
    {
        sf::VertexArray Line(sf::Lines, 2);
        Line[0].Position = sf::Vector2f(a, 0);
        Line[0].Color = sf::Color(0, 0, 0);
        Line[1].Position = sf::Vector2f(a, 768);
        Line[1].Color = sf::Color(0, 0, 0);
        MapWindow->Draw(Line);
    }

    for(int a=32; a<768; a+=32)
    {
        sf::VertexArray Line(sf::Lines, 2);
        Line[0].Position = sf::Vector2f(0, a);
        Line[0].Color = sf::Color(0, 0, 0);
        Line[1].Position = sf::Vector2f(1152, a);
        Line[1].Color = sf::Color(0, 0, 0);
        MapWindow->Draw(Line);
    }
}

void MapEditor::SaveTable()
{
    std::ofstream File(PathToCurrentMap + "MapData.txt");
    for(int a=0; a<24; a++)
    {
        for(int b=0; b<32; b++)
        {
            if(b==31)
            {
                File << TextureTable[a][b] << std::endl;
                continue;
            }
            File << TextureTable[a][b] << " ";
        }
    }
    File << std::endl; //Za lakse citanje xD
    for(int a=0; a<24; a++)
    {
        for(int b=0; b<32; b++)
        {
            if(b==31)
            {
                File << ObjectTable[a][b] << std::endl;
                continue;
            }
            File << ObjectTable[a][b] << " ";
        }
    }
}

void MapEditor::GrabTile(sf::IntRect ClickPosition)
{
    for(int y=0; y<24; y++)
    {
        for(int x=0; x<4; x++)
        {
            if(TilesetRectTable[y][x].Contains(ClickPosition.Left, ClickPosition.Top))
            {
                TrenutniTile = TilesetTable[y][x];
                return;
            }
        }
    }
}

void MapEditor::SetTile(sf::IntRect ClickPosition)
{
    for(int y=0; y<24; y++)
    {
        for(int x=0; x<32; x++)
        {
            if(RectTable[y][x].Contains(ClickPosition.Left, ClickPosition.Top))
            {
                if(Tileset[TrenutniTile]->IsObject)
                    ObjectTable[y][x] = TrenutniTile;
                else
                    TextureTable[y][x] = TrenutniTile;
                return;
            }
        }
    }
}

void MapEditor::RemoveObject(sf::IntRect ClickPosition)
{
    for(int y=0; y<24; y++)
    {
        for(int x=0; x<32; x++)
        {
            if(RectTable[y][x].Contains(ClickPosition.Left, ClickPosition.Top))
                ObjectTable[y][x] = -1;
        }
    }
}

void MapEditor::ChangeMap(bool DoIncrement)
{
    SaveTable();
    if(DoIncrement)
    {
        CurrentMapId++;
        std::stringstream convert;
        convert << CurrentMapId;
        PathToCurrentMap = "CustomWorld/Map" + convert.str() + "/";
        MapWindow->SetTitle(PathToCurrentMap + "MapData.txt");
        LoadTable();
    }
    else
    {
        --CurrentMapId;
        std::stringstream convert;
        convert << CurrentMapId;
        PathToCurrentMap = "CustomWorld/Map" + convert.str() + "/";
        MapWindow->SetTitle(PathToCurrentMap + "MapData.txt");
        LoadTable();
    }
}