#include "tweening.h"
#include <iostream>


    /// \fn float simpleLinearEquation(int currentTime, int start, int totalDistance, int totalTime)
    /// \brief une equation lineaire simple permettant de calculer une position
    /// \param timeElapsed le temps ecoulé
    /// \param start la position de départ
    /// \param totalDistance la distance a parcourir
    /// \param totalTime le temps total de parcours
    /// \return une position selon les parametres

    float simpleLinearTweening(int timeElapsed, int start, int totalDistance, int totalTime)
    {
        return totalDistance*timeElapsed/totalTime + start;
    }
