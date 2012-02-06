#ifndef CHARACTER_SCREEN_H
#define CHARACTER_SCREEN_H

/*
TODO: Pokazi lika, equipane iteme, questove i statse
//i ovo class jer treba swap izmeðu questova
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