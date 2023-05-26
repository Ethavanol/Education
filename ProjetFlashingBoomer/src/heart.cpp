#include "heart.h"

heart::heart():
    HeartPosX(0),
    HeartPosY(0),
    HeartWidth(32),
    HeartHeight(32),
    IsCollected(false),
    showHeart(true),
    hitboxRectHeart{int(HeartPosX), int(HeartPosY), int(HeartWidth), int(HeartHeight)}
{}

heart::heart(unsigned int x, unsigned int y, unsigned w, unsigned h):
    HeartPosX(x),
    HeartPosY(y),
    HeartWidth(w),
    HeartHeight(h),
    IsCollected(false),
    showHeart(true),
    hitboxRectHeart{int(HeartPosX), int(HeartPosY), int(HeartWidth), int(HeartHeight)}
{}

heart::~heart()
{}

unsigned int heart::getHeartPosX() const{
    return HeartPosX;
}

void heart::setHeartPosX(unsigned int value){
    HeartPosX = value;
}

unsigned int heart::getHeartPosY() const{
    return HeartPosY;
}

void heart::setHeartPosY(unsigned int value){
    HeartPosY = value;
}

unsigned int heart::getHeartWidth() const{
    return HeartWidth;
}

void heart::setHeartWidth(unsigned int value){
    HeartWidth = value;
}

unsigned int heart::getHeartHeight() const{
    return HeartHeight;
}

void heart::setHeartHeight(unsigned int value){
    HeartHeight = value;
}

bool heart::getIsCollected() const{
    return IsCollected;
}

void  heart::setIsCollected(bool boolean){
    IsCollected = boolean;
}

bool heart::getshowHeart() const{
    return showHeart;
}

void  heart::setshowHeart(bool boolean){
    showHeart = boolean;
}

SDL_Rect& heart::getHitboxRectHeart(){
    return hitboxRectHeart;
}

void heart::refreshHitboxHeart()
{
    SDL_Rect newhitbox{int(HeartPosX), int(HeartPosY), int(HeartWidth), int(HeartWidth)};
    hitboxRectHeart = newhitbox;
}

void heart::reset(unsigned int x, unsigned int y)
{
    HeartPosX = x;
    HeartPosY = y;
    HeartWidth = 32;
    HeartHeight = 32;

    IsCollected = false;
    showHeart = true;
}