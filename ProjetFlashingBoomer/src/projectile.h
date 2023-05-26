#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#ifndef PI
#define PI 3.14159265
#endif

#include "timer.h"
#include "tweening.h"
#include "runner.h"

#include <iostream>
using namespace std;

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>

/// \class projectile
/// \brief classe definissant les projectiles tirés par l'arme du Canon

class projectile
{
private:
    
    int posX;  ///position du projectile en abscisse
    int posY;  ///position du projectile en ordonnée

    float angle;

    unsigned int speed; ///vitesse du projectile

    unsigned int damage;    ///degats du projectile
    unsigned int blastRadius;   ///le rayon d'explosion du projectile

    bool isMoving;  ///indique le movement du projectile
    bool detonate;  ///indique si le projectile est en train d'exploser

    SDL_Rect hitbox;
    
public:

    timer Timer;

    
    projectile(/* args */);
    projectile(const projectile& p);
    projectile(unsigned int x, unsigned int y, unsigned int spd, unsigned int dmg, unsigned int blast);

    ~projectile();



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
    /// \brief accesseur de la variable angle (en degrés)
    /// \return posY

    float getAngle() const;


    /// \fn void setAngle(float value)
    /// \brief mutateur de la variable angle (en degrés)
    /// \param value nouvelle valeur de la variable

    void setAngle(float value);

    /// \fn unsigned int getSpeed() const
    /// \brief accesseur de la variable speed
    /// \return posY

    unsigned int getSpeed() const;


    /// \fn void setSpeed(unsigned int value)
    /// \brief mutateur de la variable speed
    /// \param value nouvelle valeur de la variable

    void setSpeed(unsigned int value);


    /// \fn unsigned int getDamage() const
    /// \brief accesseur de la variable damage
    /// \return posY

    unsigned int getDamage() const;


    /// \fn void setDamage(unsigned int value)
    /// \brief mutateur de la variable damage
    /// \param value nouvelle valeur de la variable

    void setDamage(unsigned int value);


    /// \fn unsigned int getBlastRadius() const
    /// \brief accesseur de la variable blastRadius
    /// \return posY

    unsigned int getBlastRadius() const;


    /// \fn void setBlastRadius(unsigned int value)
    /// \brief mutateur de la variable blastRadius
    /// \param value nouvelle valeur de la variable

    void setBlastRadius(unsigned int value);


    /// \fn unsigned int getIsMoving() const
    /// \brief accesseur de la variable isMoving
    /// \return posY

    bool getIsMoving() const;


    /// \fn void setIsMoving(unsigned int value)
    /// \brief mutateur de la variable isMoving
    /// \param value nouvelle valeur de la variable

    void setIsMoving(bool value);

    
    /// \fn unsigned int getDetonate() const
    /// \brief accesseur de la variable detonate
    /// \return posY

    bool getDetonate() const;


    /// \fn void setDetonate(unsigned int value)
    /// \brief mutateur de la variable detonate
    /// \param value nouvelle valeur de la variable

    void setDetonate(bool value);

    SDL_Rect& getHitbox();

    void setHitbox(SDL_Rect value);

    void refreshExplosion(runner& r);
    void refreshExplosion(const SDL_Rect& r);

    void travel();

    void refreshMovement();

};

#endif