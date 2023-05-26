#ifndef _MAP_H
#define _MAP_H

/// \file map.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;
#include "coin.h"
#include "heart.h"

/// \class map
/// \brief classe contenant les differents éléments de la carte

class map
{
    private:
    
    unsigned int plateformsSize;
    unsigned int sizelistCoin;
    
    public:

    vector<SDL_Rect> arrPlateforms;

    SDL_Surface* background;    ///l'image du fond
    SDL_Surface* spriteCoin;    ///m'image de la pièce
    SDL_Surface* spriteHeart;   ///l'image du coeur

    SDL_Rect backgroundRect;    ///la taille de l'image du fond 

    SDL_Rect *plateforms;   /// Tableau de rectangles correspondant aux plateformes de la map

    SDL_Rect *walls;    ///tableau de rectangles correspondant aux murs de la map

    SDL_Point runnerSpawnPoint, canonSpawnPoint; 
    
    SDL_Rect heartSpawnRect;
    

    coin *listCoinMap; /// tableau de pièces
    coin Coin;

    heart Heart;

    
    /// \fn map()
    /// \brief constructeur par défaut de la classe map
    map();

    /// \fn ~map()
    /// \brief déstructeur par défaut de la classe map
    ~map();

    /// \fn SDL_Surface* getSpriteCoin() const
    /// \brief accesseur de la surface sprite
    /// \return spriteCoin

    SDL_Surface* getSpriteCoinMap() const;

    SDL_Surface* getSpriteHeartMap() const;

    unsigned int getSizeListCoinMap() const;

    /// \fn void ListPlatforms1()
    /// \brief void pour la liste de tableau correspondant aux plateformes de la première map

    void ListPlatforms1(); 


    /// \fn void ListPlatforms2()
    /// \brief void pour la liste de tableau correspondant aux plateformes de la deuxième map

    void ListPlatforms2(); 


    /// \fn void ListPlatforms2()
    /// \brief crée une map a partir dun fichier text

    void readMapFile(int windowWidth, int windowHeight, string mapFileName);

    /// \fn void InitListCoinsMap()
    /// \brief void qui initialise les coordonnées de chacune des pièces de la liste que l'on va afficher sur la map

    void InitListCoinsMap();

    void reset();

};

#endif