#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <iostream>
using namespace std;
#include <vector>

#include <SDL2/SDL.h>
#include "projectile.h"

#include "timer.h"
#include <string.h>

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>


/// \class weapon
/// \brief classe definissant l'arme avec laquelle le Canon tire

class weapon
{
private:

    unsigned int posX;  ///la position de l'arme en obscisse (certainement la meme que celle du canon)
    unsigned int posY;  ///la position de l'arme en ordonnée (certainement la meme que celle du canon)
    float angle; ///l'angle de l'arme par rapport a l'horizon (suit theoriquement l'angle du canon)

    int projectileSpeed;    ///la vitesse des projectiles tirés par l'arme
    int damage; ///les degats des projectiles tirés par l'arme
    int blastRadius;    ///l'etendue de l'explosion provoqué par les projectiles tirés par l'arme

    unsigned int fireRate;  ///la cadence de tir de l'arme 

    SDL_Surface* weaponSprite;    ///une surface contenant les sprites de l'arme
    SDL_Surface* projectileSprite;

    int selectedSpriteFrame;

public:

    timer Timer;

    vector<projectile> arrBullet;  ///les projectiles tirées par l'arme stockées dans un tableau dynamique

    SDL_Rect* srcRectsprite;
    
    weapon();

    weapon(unsigned int x, unsigned int y);

    weapon(unsigned int x, unsigned int y, unsigned int rate, unsigned int posBulletX, unsigned int posBulletY, unsigned int spd, unsigned int dmg, unsigned int blast, string weaponSpritePth, string projectileSpritePth);
    
    ~weapon();


    /// \fn unsigned int getPosX() const
    /// \brief accesseur de la variable posX
    /// \return posX

    unsigned int getPosX() const;


    /// \fn void setPosX(unsigned int value)
    /// \brief mutateur de la variable posX
    /// \param value nouvelle valeur de la variable

    void setPosX(unsigned int value);


    /// \fn unsigned int getPosY() const
    /// \brief accesseur de la variable posY
    /// \return posY

    unsigned int getPosY() const;


    /// \fn void setPosY(unsigned int value)
    /// \brief mutateur de la variable posY
    /// \param value nouvelle valeur de la variable

    void setPosY(unsigned int value);


    /// \fn unsigned int getAngle() const
    /// \brief accesseur de la variable angle
    /// \return posY

    float getAngle() const;


    /// \fn void setAngle(float value)
    /// \brief mutateur de la variable angle
    /// \param value nouvelle valeur de la variable

    void setAngle(float value);


    /// \fn SDL_Surface* getSprite() const
    /// \brief accesseur de la surface sprite
    /// \return sprite

    SDL_Surface* getSprite() const;

    SDL_Surface* getProjectileSprite() const;

    int getSelectedSpriteFrame() const;

    void setSelectedSpriteFrame(int value);

    void createBullet(unsigned int x, unsigned int y);  //create bullet a la position indiquée

    void deleteBullet(unsigned int n);  //detruit le projectile a la position n du tableau

    bool bulletHasExploded(unsigned int n); //test si le projectile en position n du tableau a explosé 

    void refreshArrBullet();    //rafraichit le tableau de porjectile en detruisant les projectiles ayant explosé 
    
    void shoot();   //creer un projectile et l'envoie

    void destroyProjectile(int i);  //detruit un porjectile

    void refreshProjectilesMovements(); //rafraichit la hitbox des projectiles avec la position

};

#endif