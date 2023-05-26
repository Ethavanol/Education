#ifndef _BUTTON_H
#define _BUTTON_H

/// \file button.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>

/// \class button
/// \brief classe qui définit les boutons sur lesquels nous allons cliquer.

class button 
{
    private:

    unsigned int posXJouer, posYJouer, WidthJouer, HeightJouer;  ///coordonnées réelles (absolues) du bouton jouer
    unsigned int posXQuit, posYQuit, WidthQuit, HeightQuit; /// coordonnées réelles du bouton quitter
    //VARIABLES SDL

    SDL_Surface* spriteJouer;    ///sprite du bouton jouer
    SDL_Surface* spriteQuit;    ///sprite du bouton quitter
    SDL_Rect hitboxRectJouer; ///rectangle entourant le spriteJouer, coordonnées du rectangle qui s'affichera sur le rendu et que l'on modifiera
    SDL_Rect hitboxRectInit; ///rectangle initial, taille de la texture que l'on introduit
    SDL_Rect hitboxRectQuit; ///rectangle entourant le spriteQuit, coordonnées du rectangle qui s'affichera sur le rendu et que l'on modifiera

    public:
    button();

    button(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

    ~button();

    // accesseurs et mutateurs du bouton

    /// \fn unsigned int getposXJouer() const
    /// \brief accesseur de la variable posXJouer
    /// \return posXJouer

    unsigned int getposXJouer() const;


    /// \fn void setPosX(unsigned int value)
    /// \brief mutateur de la variable posXJouer
    /// \param value nouvelle valeur de la variable

    void setposXJouer(unsigned int value);


    /// \fn unsigned int getposYJouer() const
    /// \brief accesseur de la variable posYJouer
    /// \return posYJouer

    unsigned int getposYJouer() const;


    /// \fn void setposYJouer(unsigned int value)
    /// \brief mutateur de la variable posYJouer
    /// \param value nouvelle valeur de la variable

    void setposYJouer(unsigned int value);

    /// \fn unsigned int getwidthJouer() const
    /// \brief accesseur de la longueur de l'image
    /// \return WidthJouer

    unsigned int getwidthJouer() const;

    /// \fn void setwidthJouer(unsigned int value)
    /// \brief mutateur de la longueur de la hitbox
    /// \param value nouvelle valeur de la variable

    void setwidthJouer(unsigned int value);

    /// \fn unsigned int getheightJouer() const
    /// \brief accesseur de la hauteur de l'image
    /// \return WidthJouer

    unsigned int getheightJouer() const;

    /// \fn void setheightJouer(unsigned int value)
    /// \brief mutateur de la hauteur de la hitbox
    /// \param value nouvelle valeur de la variable

    void setheightJouer(unsigned int value);

    /// \fn unsigned int getposXQuit() const
    /// \brief accesseur de la variable posXQuit
    /// \return posXQuit

    unsigned int getposXQuit() const;


    /// \fn void setPosX(unsigned int value)
    /// \brief mutateur de la variable posXQuit
    /// \param value nouvelle valeur de la variable

    void setposXQuit(unsigned int value);


    /// \fn unsigned int getposYQuit() const
    /// \brief accesseur de la variable posYQuit
    /// \return posYQuit

    unsigned int getposYQuit() const;


    /// \fn void setposYQuit(unsigned int value)
    /// \brief mutateur de la variable posYQuit
    /// \param value nouvelle valeur de la variable

    void setposYQuit(unsigned int value);

    /// \fn unsigned int getwidthQuit() const
    /// \brief accesseur de la longueur de l'image
    /// \return WidthQuit

    unsigned int getwidthQuit() const;

    /// \fn void setwidthQuit(unsigned int value)
    /// \brief mutateur de la longueur de la hitbox
    /// \param value nouvelle valeur de la variable

    void setwidthQuit(unsigned int value);

    /// \fn unsigned int getheightQuit() const
    /// \brief accesseur de la hauteur de l'image
    /// \return HeightQuit

    unsigned int getheightQuit() const;

    /// \fn void setheightQuit(unsigned int value)
    /// \brief mutateur de la hauteur de la hitbox
    /// \param value nouvelle valeur de la variable

    void setheightQuit(unsigned int value);


    /// \fn SDL_Surface* getSpriteJouer() const
    /// \brief accesseur de la surface spriteJouer
    /// \return spriteJouer

    SDL_Surface* getSpriteJouer() const;

    /// \fn SDL_Surface* getSpriteQuit() const
    /// \brief accesseur de la surface spriteQuit
    /// \return spriteQuit

    SDL_Surface* getSpriteQuit() const;

    /// \fn SDL_Rect& getHitboxRectJouer()
    /// \brief accesseur de la hitbox du spriteJouer
    /// \return spriteJouer

    SDL_Rect& getHitboxRectJouer();

    SDL_Rect& getHitboxRectQuit();

    void setHitboxRectJouer(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void setHitboxRectQuit(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    /// \fn SDL_Rect& getHitboxRectInit()
    /// \brief accesseur de la hitbox du sprite initial
    /// \return spriteInitial

    SDL_Rect& getHitboxRectInit();
};

#endif