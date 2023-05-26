#ifndef _COIN_H
#define _COIN_H

/// \file coin.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include "timer.h"

/// \class coin
/// \brief classe du coin

class coin
{
private:

    unsigned int CoinPosX, CoinPosY; // Position x et y du sprite qu'on affiche 
    unsigned int CoinWidth, CoinHeight;
    bool CoinOnMap;
    unsigned int IsCollected; // 0 si non collecté, 1 sinon

   // SDL_Surface* spriteCoin;    ///sprite du runner
    SDL_Rect hitboxRectCoin;    // hitbox de la pièece que l'on souhaite affichée
    int selectedSpriteCoinFrame;    //le numero de la frame selectionnée 
    SDL_Rect currentSpriteCoinFrame;    ///la frame du sprite actuellement selectionnée

public:

    SDL_Rect* srcRectSpriteCoin;    ///tableau de SDL_Rect contenant toutes les frames des sprites

    /// \fn coin()
    /// \brief constructeur par defaut de la classe coin
    coin();

    /// \fn coin(unsigned int x, unsigned int y, unsigned int w, unsigned h)
    /// \brief constructeur de la classe coin
    coin(unsigned int x, unsigned int y, unsigned int w, unsigned int h);


    /// \fn ~coin()
    /// \brief destructeur de la classe coin
    ~coin();

    // \fn unsigned int getCoinPosX() const
    /// \brief accesseur de la variable CoinPosX
    /// \return CoinPosX

    unsigned int getCoinPosX() const;

    /// \fn void setCoinPosX(unsigned int value)
    /// \brief mutateur de la variable CoinPosX
    /// \param value nouvelle valeur de la variable

    void setCoinPosX(unsigned int value);


    /// \fn unsigned int getCoinPosY() const
    /// \brief accesseur de la variable CoinPosY
    /// \return CoinPosY

    unsigned int getCoinPosY() const;


    /// \fn void setCoinPosY(unsigned int value)
    /// \brief mutateur de la variable CoinPosY
    /// \param value nouvelle valeur de la variable

    void setCoinPosY(unsigned int value);

    /// \fn unsigned int getWidth() const
    /// \brief accesseur de la variable CoinWidth
    /// \return CoinWidth

    unsigned int getWidth() const;

    /// \fn void setCoinWidth(unsigned int value)
    /// \brief mutateur de la variable CoinWidth
    /// \param value nouvelle valeur de la variable

    void setCoinWidth(unsigned int value);

    /// \fn unsigned int getCoinHeight() const
    /// \brief accesseur de la variable CoinHeight
    /// \return CoinHeight

    unsigned int getCoinHeight() const;


    /// \fn void setCoinHeight(unsigned int value)
    /// \brief mutateur de la variable CoinHeight
    /// \param value nouvelle valeur de la variable

    void setCoinHeight(unsigned int value);

    /// \fn bool getCoinOnMap() const
    /// \brief accesseur du booléen CoinOnTheMap
    /// \return CoinOnTheMap

    bool getCoinOnMap() const;

    /// \fn void setCoinOnMap(bool boolean)
    /// \brief mutateur du booléen CoinOnTheMap
    /// \param boolean nouvelle valeur du bouléen

    void setCoinOnMap(bool boolean);

    /// \fn bool getIsCollected() const
    /// \brief accesseur du booléen IsCollected
    /// \return IsCollected

    bool getIsCollected() const;

    /// \fn void IsCollected(bool boolean)
    /// \brief mutateur du booléen IsCollected
    /// \param bool nouvelle valeur de l'entier

    void setIsCollected(bool boolean );

  /*  /// \fn SDL_Surface* getSpriteCoin() const
    /// \brief accesseur de la surface sprite
    /// \return spriteCoin

    SDL_Surface* getSpriteCoin() const; */

    /// \fn SDL_Rect& getHitboxRectCoin()
    /// \brief accesseur du rectangle hitbox
    /// \return hitboxRectCoin

    SDL_Rect& getHitboxRectCoin(); 

    /// \fn void refreshHitboxCoin()
    /// \brief redéfini les valeurs de la hitbox, nécessaire pour afficher des listes de pièces

    void refreshHitboxCoin();

    /// \fn SDL_Rect& getCurrentSpriteCoinFrame()
    /// \brief accesseur du rectangle currentSpriteCoinFrame
    /// \return currentSpriteCoinFrame

    SDL_Rect& getCurrentSpriteCoinFrame();


    /// \fn void setCurrentSpriteCoinFrame(const SDL_Rect& value)
    /// \brief mutateur du rectangle currentSpriteCoinFrame
    
    void setCurrentSpriteCoinFrame(const SDL_Rect& value);

    /// \fn int getSelectedSpriteCoinFrame() const
    /// \brief accesseur de la variable selectedSpriteCoinFrame
    /// \return selectedSpriteCoinFrame

    int getSelectedSpriteCoinFrame() const;


    /// \fn void setSelectedSpriteCoinFrame(const int& value)
    /// \brief mutateur de la variable selectedSpriteCoinFrame

    void setSelectedSpriteCoinFrame(const int& value);

    /// \fn void reset(unsigned int x, unsigned int y)
    /// \brief reinitialiseur de la classe coin

    void reset(unsigned int x, unsigned int y);
};

#endif