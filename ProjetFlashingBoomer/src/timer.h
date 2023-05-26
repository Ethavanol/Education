#ifndef _TIMER_H_
#define _TIMER_H_

/// \file timer.h


#include <SDL2/SDL.h>

/// \class timer
/// \brief classe gerant quelques actions simples en rapport avec le temps

class timer
{
private:
    Uint32 startTicks;

public:
    timer();

    /// \fn Uint32 timePassed()
    /// \brief renvoie le temps passé depuis l'appel de start

    Uint32 timePassed();

    

    /// \fn void start()
    /// \brief (re)lance le timer

    void start();
};

#endif