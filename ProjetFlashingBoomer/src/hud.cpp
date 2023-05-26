#include "hud.h"

hud::hud():
    spriteCoinHud(IMG_Load("data/coin.png")),
    spriteHeartHud(IMG_Load("data/heart.png")),
    SizelistCoin(5),
    SizelistHeart(4)
{
    listCoinScore = new coin[SizelistCoin];
    listHeart = new heart[SizelistHeart];
}

hud::~hud()
{
    SDL_FreeSurface(spriteCoinHud);
    SDL_FreeSurface(spriteHeartHud);
    delete [] listCoinScore;
    delete [] listHeart;
}

unsigned int hud::getSizelistHeart() const{
    return SizelistHeart;
}

unsigned int hud::getSizelistCoin() const{
    return SizelistCoin;
}

SDL_Surface* hud::getSpriteCoinHud() const{
    return spriteCoinHud;
}

SDL_Surface* hud::getSpriteHeartHud() const{
    return spriteHeartHud;
}

