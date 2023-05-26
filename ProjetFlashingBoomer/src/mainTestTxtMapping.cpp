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


    Game.createMapElement("data/mapfile.txt");

    

    while (Game.playLoop())  //tant qu'il y a des evenements qui ne sont pas une fermeture de fenetre ...
    {
        //Game.playLoop(&play);
    }

    //Game.AfficherTest();
    Game.destroyAndQuitSDL();
    
    return EXIT_SUCCESS;   
}