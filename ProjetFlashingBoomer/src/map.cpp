#include "map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

map::map():

    background(IMG_Load("data/background.png")),
    spriteCoin(IMG_Load("data/coin.png")),
    spriteHeart(IMG_Load("data/heartmap.png")),
    backgroundRect {0, 0, 512, 288}
{
    plateforms = new SDL_Rect[10];
    walls = new SDL_Rect[2] {{0, 0, 1, 800}, {800, 0, 1, 800}};
    plateformsSize = 0;
    listCoinMap = new coin[5];
    sizelistCoin = 5;
}

map::~map()
{
    SDL_FreeSurface(spriteCoin);
    SDL_FreeSurface(spriteHeart);
    delete [] plateforms;
    plateforms = NULL;
    delete [] walls;
    delete [] listCoinMap;
    // Attention à ne pas delete listCoinMap, car le type Coin est déjà détruit dans sa classe
}

SDL_Surface* map::getSpriteCoinMap() const{
    return spriteCoin;
}

SDL_Surface* map::getSpriteHeartMap() const{
    return spriteHeart;
}

unsigned int map::getSizeListCoinMap() const{
    return sizelistCoin;
}



void map::readMapFile(int windowWidth, int windowHeight, string mapFileName)
{
    arrPlateforms.clear();

    int squareNbW, squareNbH; //le nombre de carrés en largeur et en hauteur

    ifstream file(mapFileName.c_str());
    string line;

    getline(file, line);    //la premiere ligne du fichier correspond au nombre de carrés en largeur
    squareNbW = stoi(line);

    getline(file, line);    //la deuxieme ligne du fichier correspond au nombre de carrés en hauteur
    squareNbH = stoi(line);

    file.ignore();

    int squareSize = windowWidth/squareNbW; //la taille des cotés d'un carré 

    char tile;  //le caractere lu

    file.seekg(-1, ios::cur);   //on se positionne au debut de la map a lire


    unsigned int i = 0;
    for(int y = 0; y < squareNbH; y++)
    {
        for(int x = 0; x < squareNbW; x++)
        {
            file >> tile;
            
            if(tile == '1')
            {
                
                arrPlateforms.push_back(SDL_Rect{x*squareSize, y*squareSize, squareSize, squareSize});  //on ajoute une plateforme au tableau

            }
            else if (tile == 'R')
            {
                runnerSpawnPoint = {x*squareSize, y*squareSize};
            }
            else if (tile == 'C')
            {
                canonSpawnPoint = {x*squareSize, y*squareSize};
            }
            else if (tile == 'P' )
            {
                if(i < sizelistCoin)
                {
                    listCoinMap[i].setCoinPosX(x*squareSize);
                    listCoinMap[i].setCoinPosY(y*squareSize);
                    listCoinMap[i].setCoinWidth(squareSize);
                    listCoinMap[i].setCoinHeight(squareSize);
                    listCoinMap[i].setIsCollected(false);
                    listCoinMap[i].setCoinOnMap(true);

                    i++;
                }
            }
            else if (tile == 'H' )
            {
                heartSpawnRect = {x*squareSize, y*squareSize, squareSize, squareSize};
            }
            
        }
        
    }
    file.close();
}
