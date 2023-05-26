#include "timer.h"

timer::timer()
{
    start();
}

Uint32 timer::timePassed()
{
        return SDL_GetTicks() - startTicks;
}

void timer::start()
{
    startTicks = SDL_GetTicks();
}

