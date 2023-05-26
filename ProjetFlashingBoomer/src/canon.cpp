#include "canon.h"


canon::canon():
    posX(0),
    posY(0),
    angle(0),

    sprite(IMG_Load("data/canon_spritev2.png")),

    hitboxRectInit {0, 0, 128, 128},
    hitboxRect {int(posX), int(posY), 100, 100}, //a modifier quand sprite animé

    Weapon(0, 0)
{
    weaponDestSpriteRect = {int(posX-hitboxRect.w/2), int(posY-hitboxRect.h/2), hitboxRect.w*2, hitboxRect.h*2};
 }

canon::canon(unsigned int x, unsigned int y):
    posX(x),
    posY(y),
    angle(0),

    sprite(IMG_Load("data/canon_spritev2.png")),
    hitboxRectInit {0, 0, 128, 128},
    hitboxRect {int(posX), int(posY), 100, 100}, //a modifier quand sprite animé

    Weapon(x, y)
{
    weaponDestSpriteRect = {int(posX-hitboxRect.w/2), int(posY-hitboxRect.h/2), hitboxRect.w*2, hitboxRect.h*2};
}

canon::~canon()
{
    SDL_FreeSurface(sprite);
}

unsigned int canon::getPosX() const
{
    return posX;
}

void canon::setPosX(unsigned int value)
{
    posX = value;
}

unsigned int canon::getPosY() const
{
    return posY;
}

void canon::setPosY(unsigned int value)
{
    posY = value;
}

float canon::getAngle() const
{
    return angle;
}

void canon::setAngle(float value)
{
    angle = value;
}

SDL_Surface* canon::getSprite() const
{
    return sprite;
}

SDL_Rect& canon::getHitboxRect()
{
    return hitboxRect;
}

SDL_Rect& canon::getHitboxRectInit()
{
    return hitboxRectInit;
}

SDL_Rect& canon::getWeaponDestSpriteRect()
{
    return weaponDestSpriteRect;
}

void canon::refreshAngles()
{
    Weapon.setAngle(getAngle());
}

void canon::refreshPosition()
{

    Weapon.setPosX(posX);
    Weapon.setPosY(posY);
    hitboxRect = {int(posX), int(posY), 100, 100};

    weaponDestSpriteRect = {int(posX-hitboxRect.w/2), int(posY-hitboxRect.h/2), hitboxRect.w*2, hitboxRect.h*2};
}

void canon::reset(unsigned int x, unsigned int y)
{
    posX = x;
    posY = y;
    angle = 0;
    Weapon.setPosX(x);
    Weapon.setPosY(y);

    Weapon.arrBullet.clear();
}