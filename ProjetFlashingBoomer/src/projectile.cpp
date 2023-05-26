#include "projectile.h"
#include <math.h>


projectile::projectile()
{}

projectile::projectile(const projectile& p)
{
    this->posX = p.posX;
    this->posY = p.posY;
    this->angle = p.angle;
    this->speed = p.speed;
    this->damage = p.damage;
    this->blastRadius = p.blastRadius;
    this->isMoving = p.isMoving;
    this->detonate = p.detonate;
    this->hitbox = p.hitbox;
}

projectile::projectile(unsigned int x, unsigned int y, unsigned int spd, unsigned int dmg, unsigned int blast):
    posX(x),
    posY(y),

    speed(spd),

    damage(dmg),
    blastRadius(blast),

    isMoving(false),
    detonate(false),

    hitbox{posX, posY, 16, 16}

    
{}

projectile::~projectile()
{}

unsigned int projectile::getPosX() const
{
    return posX;
}

void projectile::setPosX(unsigned int value)
{
    posX = value;
}

unsigned int projectile::getPosY() const
{
    return posY;
}

void projectile::setPosY(unsigned int value)
{
    posY = value;
}

float projectile::getAngle() const
{
    return angle;
}

void projectile::setAngle(float value)
{
    angle = value;
}

unsigned int projectile::getSpeed() const
{
    return speed;
}

void projectile::setSpeed(unsigned int value)
{
    speed = value;
}

unsigned int projectile::getDamage() const
{
    return damage;    
}

void projectile::setDamage(unsigned int value)
{
    damage = value;
}

unsigned int projectile::getBlastRadius() const
{
    return blastRadius;
}

void projectile::setBlastRadius(unsigned int value)
{
    blastRadius = value;
}

bool projectile::getIsMoving() const
{
    return isMoving;
}

void projectile::setIsMoving(bool value)
{
    isMoving = value;
}

bool projectile::getDetonate() const
{
    return detonate;
}

void projectile::setDetonate(bool value)
{
    detonate = value;
}

SDL_Rect& projectile::getHitbox()
{
    return hitbox;
}

void projectile::refreshExplosion(runner& r)   //gere la collision entre le joueur et le projectile
{
    if(SDL_HasIntersection(&r.getHitboxRect(), &hitbox))
    {
        //r.setLife(r.getLife() - damage);
        if(r.getLife() != 0)
        {
            r.loseALife();
        }
        detonate = true;
        isMoving = false;
    }
}

void projectile::refreshExplosion(const SDL_Rect& r)    //gere la collision entre un rectangle et le projectile 
{
    if(SDL_HasIntersection(&r, &hitbox))
    {
        detonate = true;
        isMoving = false;
    }
}

void projectile::travel()
{
    posX += int(speed * cos(angle));
    posY -= int(speed * sin(angle));
    
}

void projectile::refreshMovement()
{
    if(isMoving)
    {
        travel();
        hitbox.x = posX;
        hitbox.y = posY;
    }
}