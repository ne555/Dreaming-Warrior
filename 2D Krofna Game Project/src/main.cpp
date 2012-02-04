/*
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
  copy(istream_iterator<int>(ifstream("entree.txt")),istream_iterator<int>(),ostream_iterator<int>(ofstream("sortie.txt"), " "));
  return 0;
} 
*/
#include "game.h"

int main()
{
    srand((unsigned)time(0));
    Game Game;
    Game.InitGame(Game.ShowMenu());
    Game.GameLoop();
}