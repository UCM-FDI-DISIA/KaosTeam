// Frog.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "game/Game.h"

#include <iostream>
#include <array>
#include <string>

int main(int ac, char** av)
{
    Game game = Game();
    game.init();

    //delete game;

    return 0;
}