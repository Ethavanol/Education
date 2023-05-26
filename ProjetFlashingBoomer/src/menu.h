#ifndef _MENU_H
#define _MENU_H

/// \file menu.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>

/// \class menu
/// \brief classe contenant les differents éléments du menu

class menu
{
    private:
    
    public:

    SDL_Surface* backgroundMenu;    ///l'image du fond

    menu();

    ~menu();

};

#endif