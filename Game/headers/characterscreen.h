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
#ifndef CHARACTER_SCREEN_H
#define CHARACTER_SCREEN_H

/*
TODO: Pokazi lika, equipane iteme, questove i statse
//i ovo class jer treba swap izme�u questova
*/
/*void Game::ShowCharacterScreen()
{
    sf::Texture BackgroundTexture;
    //BackgroundTexture.LoadFromFile("");
    sf::Sprite BackgroundSprite(BackgroundTexture);
    sf::Texture PlayerTexture;
    //PlayerTexture.LoadFromFile("");
    sf::Sprite PlayerSprite(PlayerTexture);
    //PlayerSprite.SetPosition();

    // bla bla PH
}*/
/*
TODO: Pokazi lika, backpack iteme, omoguci mjenjanje statsa, omoguci mjenjanje equipa
*/

class Player;

class CharacterScreen
{
public:
    CharacterScreen(Player &Player);
};

#endif