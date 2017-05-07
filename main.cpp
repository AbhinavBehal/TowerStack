#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Game.h"

int main()
{
    srand(time(0));
    Game game;
    game.start();

    return 0;
}
