#ifndef _HUD_H
#define _HUD_H

/// \file hud.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
//#include <SDL2/SDL_ttf.h>
#include "coin.h"
#include "heart.h"
//#include "write.h"

/// \class hud
/// \brief classe contenant les differents éléments de la carte

class hud
{
    private:

        unsigned int SizelistCoin;
        unsigned int SizelistHeart;  

    public:

        SDL_Surface* spriteCoinHud;
        SDL_Surface* spriteHeartHud;

        coin *listCoinScore; /// tableau de pièces
        coin Coin;

        heart *listHeart;
        heart Heart;

        /// \fn hud()
        /// \brief constructeur par défaut de la classe hud
        hud();

        /// \fn ~hud()
        /// \brief déstructeur par défaut de la classe hud
        ~hud();

       // int testerreur();

        /// \fn int getSizelistHeart() const
        /// \brief accesseur de l'entier SizelistHeart
        /// \return SizelistHeart

        unsigned int getSizelistHeart() const;

        /// \fn int getSizelistCoin() const
        /// \brief accesseur de l'entier SizelistCoin
        /// \return SizelistCoin

        unsigned int getSizelistCoin() const;

        /// \fn SDL_Surface* getSpriteCoinHud() const
        /// \brief accesseur de la surface spriteCoinHud
        /// \return spriteCoinHud

        SDL_Surface* getSpriteCoinHud() const;

        /// \fn SDL_Surface* getSpriteHeartHud() const
        /// \brief accesseur de la surface spriteHeartHud
        /// \return spriteHeartHud
        SDL_Surface* getSpriteHeartHud() const;

        void reset();

};

#endif
