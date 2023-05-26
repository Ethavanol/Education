#include "game.h"


#include <SDL2/SDL.h>
#include <cstdlib>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    game Game;

    if (Game.init_SDL() < 0)   //initialisation et test de la SDL
    {
        return EXIT_FAILURE;
    }

    if (Game.init_WinRenTex() < 0)
    {
        return EXIT_FAILURE;
    }


    while (Game.eventLoop())  //tant qu'il y a des evenements qui ne sont pas une fermeture de fenetre ...
    {
        //Game.display();
    }

    Game.destroyAndQuitSDL();
    
    return EXIT_SUCCESS;
}