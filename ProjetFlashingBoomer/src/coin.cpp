#include "coin.h"

coin::coin():
    CoinPosX(200),
    CoinPosY(200),
    CoinWidth(32),
    CoinHeight(32),
    CoinOnMap(true),
    IsCollected(false),
    hitboxRectCoin{int(CoinPosX), int(CoinPosY), 30, 30}
{
    srcRectSpriteCoin = new SDL_Rect[4] {{0, 0, 32, 32}, {32, 0, 32, 32}, {0, 32, 32, 32}, {32, 32, 32, 32}}; //ligne de sprite 1 [0], [1], [2], [3]                             
    selectedSpriteCoinFrame = 0;
    currentSpriteCoinFrame = srcRectSpriteCoin[0];
}


coin::coin(unsigned int x, unsigned int y, unsigned int w, unsigned int h):
    CoinPosX(x),
    CoinPosY(y),
    CoinWidth(w),
    CoinHeight(h),
    CoinOnMap(true),
    hitboxRectCoin{int(CoinPosX), int(CoinPosY), int(CoinWidth), int(CoinHeight)}
{
    srcRectSpriteCoin = new SDL_Rect[4] {{0, 0, 32, 32}, {32, 0, 32, 32}, {64, 0, 32, 32}, {96, 0, 32, 32}}; //ligne de sprite 1 [0], [1], [2], [3]                             
    selectedSpriteCoinFrame = 0;
    currentSpriteCoinFrame = srcRectSpriteCoin[0];
}

coin::~coin()
{
    delete [] srcRectSpriteCoin;
} 

unsigned int coin::getCoinPosX() const{
    return CoinPosX;
}

void coin::setCoinPosX(unsigned int value){
    CoinPosX = value;
}

unsigned int coin::getCoinPosY() const{
    return CoinPosY;
}

void coin::setCoinPosY(unsigned int value){
    CoinPosY = value;
}

unsigned int coin::getWidth() const{
    return CoinWidth;
}

void coin::setCoinWidth(unsigned int value){
    CoinWidth = value;
}

unsigned int coin::getCoinHeight() const{
    return CoinHeight;
}

void coin::setCoinHeight(unsigned int value){
    CoinHeight = value;
}

bool coin::getCoinOnMap() const{
    return CoinOnMap;
}

void coin::setCoinOnMap(bool boolean){
    CoinOnMap = boolean;
}

bool coin::getIsCollected() const{
    return IsCollected;
}

void coin::setIsCollected(bool boolean ){
    IsCollected = boolean;
}

SDL_Rect& coin::getHitboxRectCoin(){
    return hitboxRectCoin;
}

void coin::refreshHitboxCoin()
{
    SDL_Rect newhitbox{int(CoinPosX), int(CoinPosY), int(CoinWidth), int(CoinHeight)};
    hitboxRectCoin = newhitbox;
}

SDL_Rect& coin::getCurrentSpriteCoinFrame()
{
    return currentSpriteCoinFrame;
}

void coin::setCurrentSpriteCoinFrame(const SDL_Rect& value)
{
    currentSpriteCoinFrame = value;
}

int coin::getSelectedSpriteCoinFrame() const
{
    return selectedSpriteCoinFrame;
}

void coin::setSelectedSpriteCoinFrame(const int& value)
{
    selectedSpriteCoinFrame = value;
}

void coin::reset(unsigned int x, unsigned int y)
{
    CoinPosX = x;
    CoinPosY = y;
    CoinWidth = 30;
    CoinHeight = 30;

    CoinOnMap = true;
    IsCollected = false;
}
