#ifndef _HEART_H
#define _HEART_H

/// \file heart.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include "timer.h"

/// \class heart
/// \brief classe du heart

class heart
{
    private:

    unsigned int HeartPosX, HeartPosY;
    unsigned int HeartWidth, HeartHeight;
    bool IsCollected; //Renvoie True si on collecte le coeur
    bool showHeart; //True si on affiche le coeur en question

    SDL_Rect hitboxRectHeart; //hitbox du coeur que l'on veut afficher

    public:

    /// \fn heart()
    /// \brief constructeur par defaut de la classe heart
    heart();

    /// \fn heart(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
    /// \brief constructeur de la classe heart
    heart(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    /// \fn ~heart()
    /// \brief destructeur de la classe heart
    ~heart();

    /// \fn unsigned int getHeartPosX() const
    /// \brief accesseur de la variable HeartPosX
    /// \return HeartPosX

    unsigned int getHeartPosX() const;

    /// \fn void setHeartPosX(unsigned int value)
    /// \brief mutateur de la variable HeartPosX
    /// \param value la nouvelle valeur de HeartPosX

    void setHeartPosX(unsigned int value);

    /// \fn unsigned int getHeartPosY() const
    /// \brief accesseur de la variable HeartPosY
    /// \return HeartPosY

    unsigned int getHeartPosY() const;

    /// \fn void setHeartPosY(unsigned int value)
    /// \brief mutateur de la variable HeartPosY
    /// \param value la nouvelle valeur de HeartPosY

    void setHeartPosY(unsigned int value);

    /// \fn unsigned int getHeartWidth() const
    /// \brief accesseur de la variable HeartWidth
    /// \return HeartWidth

    unsigned int getHeartWidth() const;

    /// \fn void setHeartWidth(unsigned int value)
    /// \brief mutateur de la variable HeartWidth
    /// \param value la nouvelle valeur de HeartWidth

    void setHeartWidth(unsigned int value);

    /// \fn unsigned int getHeartHeight() const
    /// \brief accesseur de la variable HeartHeight
    /// \return HeartHeight

    unsigned int getHeartHeight() const;

    /// \fn void setHeartHeight(unsigned int value)
    /// \brief mutateur de la variable HeartHeight
    /// \param value la nouvelle valeur de HeartHeight

    void setHeartHeight(unsigned int value);

    /// \fn getIsCollected() const
    /// \brief accesseur du booléen IsCollected
    /// \return IsCollected

    bool getIsCollected() const;

    /// \fn setIsCollected(bool boolean)
    /// \brief mutateur du booléen IsCollected
    /// \param boolean nouvelle valeur du booléen

    void  setIsCollected(bool boolean);

    /// \fn getshowHeart() const
    /// \brief accesseur du booléen showHeart
    /// \return showHeart

    bool getshowHeart() const;

    /// \fn setshowHeart(bool boolean)
    /// \brief mutateur du booléen showHeart
    /// \param boolean nouvelle valeur du booléen

    void  setshowHeart(bool boolean);

    /// \fn SDL_Rect& getHitboxRectHeart()
    /// \brief accesseur du rectangle hitbox
    /// \return hitboxRectHeart

    SDL_Rect& getHitboxRectHeart(); 

    /// \fn void refreshHitboxHeart()
    /// \brief redéfini les valeurs de la hitbox, nécessaire pour afficher des listes de coeurs

    void refreshHitboxHeart();

    /// \fn void reset(unsigned int x, unsigned int y)
    /// \brief réinitialiseur de la classe heart;

    void reset(unsigned int x, unsigned int y);
};

#endif