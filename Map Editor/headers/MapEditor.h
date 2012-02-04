#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

class MapEditor
{
public:
    MapEditor(sf::RenderWindow &Window);

    void SaveTable();
	void ShowMap();

    struct Tile
    {
        Tile(sf::Texture _Texture, bool Object)
        {
            Texture = _Texture;
            IsObject = Object;
        }

        sf::Texture Texture;
        bool IsObject;
    };
    std::vector<Tile*> Tileset;

    void SetTile(sf::IntRect ClickPosition);
    void GrabTile(sf::IntRect ClickPosition);
    void RemoveObject(sf::IntRect ClickPosition);
    void ChangeMap(bool DoIncrement);

private:
    void LoadTable();
    void LoadTileset();

    sf::RenderWindow* MapWindow;
    std::string PathToCurrentMap;
    int CurrentMapId;

    int TextureTable[24][32];
    int ObjectTable[24][32];
    sf::IntRect RectTable[24][32];

    std::vector<int[24][4]> novatilesettabla;

    int TilesetTable[24][4];
    sf::IntRect TilesetRectTable[24][4];

    int BrojTiles;
    int TrenutniTile;
};

#endif