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
    std::vector<Tile> Tileset;

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

    int TilesetTable[24][8];
    sf::IntRect TilesetRectTable[24][8];

    int BrojTiles;
    int TrenutniTile;
};

#endif