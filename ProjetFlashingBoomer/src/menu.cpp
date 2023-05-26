#include "menu.h"

menu::menu():

    backgroundMenu(IMG_Load("data/menu.png"))
    {}

menu::~menu()
{
    SDL_FreeSurface(backgroundMenu);
}