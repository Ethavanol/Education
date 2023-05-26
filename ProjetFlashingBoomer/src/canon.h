#ifndef _CANON_H_
#define _CANON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>

#include "weapon.h"

/// \class canon
/// \brief classe definissant le Canon

class canon
{
private:

    unsigned int posX, posY;  ///coordonnées réelles (absolues) du joueur sur la carte (coin en haut a gauche du sprite)
    float angle; ///l'angle du canon par rapport a l'horizon
    //VARIABLES SDL

    SDL_Surface* sprite;    ///sprite du runner
    SDL_Rect hitboxRectInit; ///rectangle initial, taille de la texture que l'on introduit
    SDL_Rect hitboxRect; ///rectangle entourant le sprite, coordonnées du rectangle qui s'affichera sur le rendu et que l'on modifiera
   
 
    int selectedSpriteFrame;    //le numero de la frame selectionnée 
    SDL_Rect currentSpriteFrame;    ///la frame du sprite actuellement selectionnée

    SDL_Rect weaponDestSpriteRect;  ///rectangle (dest) calculé en fonction de la postion du canon permettant de superposer le canon sur le weapon (car les deux sprites n'ont pas la meme taille)

public:
    weapon Weapon;

    canon();
    canon(unsigned int x, unsigned int y);

    ~canon();

    //ACCESSEURS ET MUTATEURS

    /// \fn bool getWin() const
    /// \brief accesseur de la variable win
    /// \return win

    bool getWin() const;


    /// \fn void setWin(unsigned int value)
    /// \brief mutateur de la variable win
    /// \param value nouvelle valeur de la variable

    void setWin(bool value);


    /// \fn unsigned int getPosX() const
    /// \brief accesseur de la variable posX
    /// \return posX

    unsigned int getPosX() const;


    /// \fn void setPosX(unsigned int value)
    /// \brief mutateur de la variable posX
    /// \param value nouvelle valeur de la variable

    void setPosX(unsigned int value);


    /// \fn unsigned int getPosY() const
    /// \brief accesseur de la variable posY
    /// \return posY

    unsigned int getPosY() const;


    /// \fn void setPosY(unsigned int value)
    /// \brief mutateur de la variable posY
    /// \param value nouvelle valeur de la variable

    void setPosY(unsigned int value);


    /// \fn unsigned int getAngle() const
    /// \brief accesseur de la variable angle
    /// \return posY

    float getAngle() const;


    /// \fn void setAngle(float value)
    /// \brief mutateur de la variable angle
    /// \param value nouvelle valeur de la variable

    void setAngle(float value);

    /// \fn SDL_Surface* getSprite() const
    /// \brief accesseur de la surface sprite
    /// \return sprite

    SDL_Surface* getSprite() const;

    /// \fn SDL_Rect& getHitboxRect()
    /// \brief accesseur de la hitbox du sprite que dont l'on modifiera les coordonnées
    /// \return sprite
    
    SDL_Rect& getHitboxRect();

    /// \fn SDL_Rect& getHitboxRectInit()
    /// \brief accesseur de la hitbox du sprite initial
    /// \return spriteInitial

    SDL_Rect& getHitboxRectInit();


    /// \fn SDL_Rect& getWeaponDestSpriteRect()
    /// \brief accesseur de la hitbox de destination
    /// \return weaponDestSpriteRect

    SDL_Rect& getWeaponDestSpriteRect();


    /// \fn void refreshAngles();
    /// \brief rafraichit l'angle de weapon avec celui de canon

    void refreshAngles();


    /// \fn void refreshPosition()
    /// \brief rafraichit la position du canon et de ces instances

    void refreshPosition();

    
    /// \fn void refreshPosition()
    /// \brief reinitialise toutes les variables du canon 
    /// \param x position en abscisse du canon
    /// \param y position en ordonnée du canon

    void reset(unsigned int x, unsigned int y);
};



#endif