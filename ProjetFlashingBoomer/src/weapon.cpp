#include "weapon.h"
#include "projectile.h"


weapon::weapon():
    posX(0),
    posY(0),
    angle(0),

    projectileSpeed(10),
    damage(1),
    blastRadius(0), 
    
    fireRate(1),

    weaponSprite(IMG_Load("data/weapon_sprite.png")),
    projectileSprite(IMG_Load("data/defaultBullet.png")),

    selectedSpriteFrame(0)

{
    
    srcRectsprite = new SDL_Rect [16];

    for(int i = 0; i < 16; i++)
    {
        srcRectsprite[i] = {64*i, 0, 64, 64};
    }
}
 
weapon::weapon(unsigned int x, unsigned int y):
    posX(y),
    posY(y),
    angle(0),

    projectileSpeed(10),
    damage(1),
    blastRadius(0),


    fireRate(1),

    weaponSprite(IMG_Load("data/weapon_sprite.png")),
    projectileSprite(IMG_Load("data/defaultBullet.png")),
    selectedSpriteFrame(0)


    //arrBullet(new projectile[projectileNumber])   //(0, 0, 0, 0, 0, NULL)

{
    srcRectsprite = new SDL_Rect [16];

    for(int i = 0; i < 16; i++) 
    {
        srcRectsprite[i] = {64*i, 0, 64, 64};
    }
}

weapon::weapon(unsigned int x, unsigned int y, unsigned int rate, unsigned int posBulletX, unsigned int posBulletY, unsigned int spd, unsigned int dmg, unsigned int blast, string weaponSpritePth, string projectileSpritePth):
    posX(x),
    posY(y),
    angle(0),

    projectileSpeed(spd),
    damage(dmg),
    blastRadius(blast),
    
    fireRate(rate),

    weaponSprite(IMG_Load(weaponSpritePth.c_str())),
    projectileSprite(IMG_Load("data/defaultBullet.png")),

    selectedSpriteFrame(0)

    //arrBullet(new projectile[projectileNumber])   //(0, 0, 0, 0, 0, NULL)

{
    srcRectsprite = new SDL_Rect [16];

    for(int i = 0; i < 16; i++)
    {
        srcRectsprite[i] = {64*i, 0, 64, 64};
    }
}

weapon::~weapon()
{
    SDL_FreeSurface(weaponSprite);
    SDL_FreeSurface(projectileSprite);
    delete [] srcRectsprite;
    arrBullet.clear();
}

unsigned int weapon::getPosX() const
{
    return posX;
}

void weapon::setPosX(unsigned int value)
{
    posX = value;
}

unsigned int weapon::getPosY() const
{
    return posY;
}

void weapon::setPosY(unsigned int value)
{
    posY = value;
}

float weapon::getAngle() const
{
    return angle;
}

void weapon::setAngle(float value)
{
    angle = value;
}

SDL_Surface* weapon::getSprite() const
{
    return weaponSprite;
}
SDL_Surface* weapon::getProjectileSprite() const
{
    return projectileSprite;
}

int weapon::getSelectedSpriteFrame() const
{
    return selectedSpriteFrame;
}

void weapon::setSelectedSpriteFrame(int value)
{
    selectedSpriteFrame = value;
}

void weapon::createBullet(unsigned int x, unsigned int y)
{
    arrBullet.push_back(projectile(x, y, projectileSpeed, damage, blastRadius));
}


void weapon::shoot()    //pour tirer
{
    if(Timer.timePassed() > 500)
    {
        createBullet(posX + 38 , posY + 38);   //on cree un projectile (au centre de la surface de l'arme)
        arrBullet.back().setAngle(angle);    //on lui donne l'angle 
        arrBullet.back().setIsMoving(true);  //puis on le met en mouvement
        Timer.start();
   }
}

void weapon::destroyProjectile(int i)   //detruit le projectile s'il a explosé 
{
    if(arrBullet[i].getDetonate())
    {
        arrBullet.erase(arrBullet.begin() + i);
    }
}

void weapon::refreshProjectilesMovements()   //rafraichit la postition des projectiles
{
    for(int i = 0; i < int(arrBullet.size()); i++)
    {
        destroyProjectile(i);
        arrBullet[i].refreshMovement();
    }
}