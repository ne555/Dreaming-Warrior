/*
    Dreaming Warrior
    Copyright (C) 2012 Mislav Blazevic

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
Dear reader of this code. Please don't kill me. 
Instead, look for Dreaming Warrior REWRITE repository.
Thanks.
*/
#include "game.h"
#include "database.h"

//todo napraviti novi text class koji inherita sf::text da bude jednostavniji kod

int main()
{
    ofstream file("Error Log.txt");
    cerr.rdbuf(file.rdbuf());

    srand((unsigned)time(0));
    Game Game;
    Game.InitGame(Game.ShowMenu());
    Game.GameLoop();
}