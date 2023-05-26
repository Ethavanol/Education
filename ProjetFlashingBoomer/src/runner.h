#ifndef _RUNNER_H_
#define _RUNNER_H_

/// \file runner.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include "line.h"

#include "timer.h"

#include <iostream>
#include <vector>
using namespace std;

/// \class runner
/// \brief classe du Runner (personnage qui court)

class runner
{
private:
    unsigned int life;  ///vie du runner
    unsigned int nbItem;   ///nombre d'objets collectés
    bool win;   ///le runner a-t-il gagné la manche

    const unsigned int baseSpeed;    ///vitesse de déplacement de base du joueur sur l'axe des abscisses
    const unsigned int baseJumpH;   ///hauteur de saut de base du joueur
    int jumpSpeed;  //vitesse de saut
    int speed;  ///vitesse de déplacement actuelle du joueur sur l'axe des abscisses
    unsigned int jumpH;  ///hauteur de saut du joueur
    unsigned int absPosX, absPosY;  ///coordonnées réelles (absolues) du joueur sur la carte (coin en haut a gauche du sprite)
    unsigned int relPosX, relPosY;  ///coordonnées futures (relatives) du joueur sur la carte (coin en haut a gauche du sprite)
    unsigned int Width, Height;
    bool isMoving;  ///le runner est il en mouvement?
    bool isGoingLeft;
    bool isGoingRight;
    bool isJumping; ///le runner saute-t-il N
    bool isTouchingGround;
    
    
    //VARIABLES SDL

    SDL_Surface* sprite;    ///sprite du runner
    SDL_Rect hitboxRect; ///rectangle entourant le sprite
    SDL_Rect hitboxRectRel; //la position future du sprite si l'on saute
 
    int selectedSpriteFrame;    //le numero de la frame selectionnée 
    SDL_Rect currentSpriteFrame;    ///la frame du sprite actuellement selectionnée

public:

    SDL_Rect* srcRectSprite;    ///tableau de SDL_Rect contenant toutes les frames des sprites


    /// \fn runner()
    /// \brief constructeur par defaut de la classe

    runner();

    /// \fn runner(unsigned int x, unsigned int y)
    /// \brief constructeur de la classe

    runner(unsigned int x, unsigned int y, unsigned int w, unsigned int h);


    /// \fn runner()
    /// \brief destructeur de la classe

    ~runner();


//ACCESSEUR ET MUTATEUR (par ordre de variable)


    /// \fn unsigned int getLife() const
    /// \brief accesseur de la variable Life
    /// \return life

    unsigned int getLife() const;


    /// \fn void setLife(unsigned int value)
    /// \brief mutateur de la variable life
    /// \param value nouvelle valeur de la variable

    void setLife(unsigned int value);


    /// \fn unsigned int getNbItem() const
    /// \brief accesseur de la variable nbItem
    /// \return nbItem

    unsigned int getNbItem() const;

    /// \fn void setNbItem(unsigned int value)
    /// \brief mutateur de la variable 
    /// \param value nouvelle valeur de la variable

    void setNbItem(unsigned int value);


    /// \fn bool getWin() const
    /// \brief accesseur de la variable win
    /// \return win

    bool getWin() const;


    /// \fn void setWin(unsigned int value)
    /// \brief mutateur de la variable win
    /// \param value nouvelle valeur de la variable

    void setWin(bool value);

    /// \fn unsigned int getBaseSpeed() const
    /// \brief accesseur de la variable baseSpeed
    /// \return baseSpeed

    unsigned int getBaseSpeed() const;


    /// \fn int getSpeed() const
    /// \brief accesseur de la variable speed
    /// \return speed

    int getSpeed() const;


    /// \fn void setSpeed(unsigned int value)
    /// \brief mutateur de la variable speed
    /// \param value nouvelle valeur de la variable

    void setSpeed(int value);


    /// \fn unsigned int getJumpH() const
    /// \brief accesseur de la variable jumpH
    /// \return jumpH

    unsigned int getJumpH() const;


    /// \fn void setJumpH(unsigned int value)
    /// \brief mutateur de la variable jumpH
    /// \param value nouvelle valeur de la variable

    void setJumpH(unsigned int value);


    /// \fn unsigned int getAbsPosX() const
    /// \brief accesseur de la variable absPosX
    /// \return absPosX

    unsigned int getAbsPosX() const;


    /// \fn void setAbsPosX(unsigned int value)
    /// \brief mutateur de la variable absPosX
    /// \param value nouvelle valeur de la variable

    void setAbsPosX(unsigned int value);


    /// \fn unsigned int getAbsPosY() const
    /// \brief accesseur de la variable absPosY
    /// \return absPosY

    unsigned int getAbsPosY() const;


    /// \fn void setAbsPosY(unsigned int value)
    /// \brief mutateur de la variable absPosY
    /// \param value nouvelle valeur de la variable

    void setAbsPosY(unsigned int value);

    /// \fn unsigned int getAbsPosX() const
    /// \brief accesseur de la variable relPosX
    /// \return absPosX

    unsigned int getRelPosX() const;


    /// \fn void setRelPosX(unsigned int value)
    /// \brief mutateur de la variable relPosX
    /// \param value nouvelle valeur de la variable

    void setRelPosX(unsigned int value);


    /// \fn unsigned int getRelPosY() const
    /// \brief accesseur de la variable relPosY
    /// \return relPosY

    unsigned int getRelPosY() const;


    /// \fn void setRelPosY(unsigned int value)
    /// \brief mutateur de la variable relPosY
    /// \param value nouvelle valeur de la variable

    void setRelPosY(unsigned int value);

    /// \fn unsigned int getWidth() const;
    /// \brief accesseur de la variale Width
    /// \return Width

    unsigned int getWidth() const{
        return Width;
    }

    /// \fn void setWidth(unsigned int value)
    /// \brief mutateur de la variale Width
    /// \param value nouvelle valeur de la variable

    void setWidth(unsigned int value){
        Width = value;
    }

    /// \fn unsigned int getHeight() const;
    /// \brief accesseur de la variale Height
    /// \return Height

    unsigned int getHeight() const{
        return Height;
    }

    /// \fn unsigned int getHeight() const;
    /// \brief accesseur de la variale Height
    /// \return Height

   void setHeight(unsigned int value){
        Height = value;
    }

    /// \fn SDL_Surface* getSprite() const
    /// \brief accesseur de la surface sprite
    /// \return sprite

    SDL_Surface* getSprite() const;


    /// \fn SDL_Rect& getHitboxRect()
    /// \brief accesseur du rectangle hitbox
    /// \return hitbox

    SDL_Rect& getHitboxRect();  //pas besoin de mutateur : la hitbox est modifié lors des déplacement (pour le moment) (potentiellement lors des animations aussi)

    SDL_Rect& getHitboxRelRect();

    /// \fn SDL_Rect& getCurrentSpriteFrame()
    /// \brief accesseur du rectangle currentSpriteFrame
    /// \return currentSpriteFrame

    SDL_Rect& getCurrentSpriteFrame();


    /// \fn void setCurrentSpriteFrame(const SDL_Rect& value)
    /// \brief mutateur du rectangle currentSpriteFrame
    
    void setCurrentSpriteFrame(const SDL_Rect& value);

    /// \fn int getSelectedSpriteFrame() const
    /// \brief accesseur de la variable selectedSpriteFrame
    /// \return selectedSpriteFrame

    int getSelectedSpriteFrame() const;


    /// \fn void setSelectedSpriteFrame(const int& value)
    /// \brief mutateur de la variable selectedSpriteFrame

    void setSelectedSpriteFrame(const int& value);

    /// \fn bool getIsMoving() const
    /// \brief accesseur de la variable isMoving
    /// \return isMoving

    bool getIsMoving() const;

    /// \fn void setIsMoving(const bool& value)
    /// \brief mutateur de la variable booléenne isMoving

    void setIsMoving(const bool& value);

    /// \fn bool getIsGoingLeft() const
    /// \brief accesseur de la variable isGoingLeft

    bool getIsGoingLeft() const;


    /// \fn void setIsGoingLeft(const bool& value)
    /// \brief mutateur de la variable isGoingLeft

    void setIsGoingLeft(const bool& value);


    /// \fn bool getIsGoingRight() const
    /// \brief accesseur de la variable isGoingRight

    bool getIsGoingRight() const;


    /// \fn void setIsGoingRight(const bool& value)
    /// \brief mutateur de la variable isGoingRight

    void setIsGoingRight(const bool& value);
    

    /// \fn bool getIsJumping() const
    /// \brief accesseur de la variable isJumping

    bool getIsJumping() const;


    /// \fn void setIsJumping(const bool& value)
    /// \brief mutateur de la variable isJumping

    void setIsJumping(const bool& value);


    /// \fn bool getIsTouchingGround() const
    /// \brief accesseur de la variable isTouchingGround

    bool getIsTouchingGround() const;


    /// \fn void setIsTouchingGround(const bool& value)
    /// \brief mutateur de la variable isTouchingGround

    void setIsTouchingGround(const bool& value);



//FONCTION ET PROCEDURES RACCOURCIES

    /// \fn void gainAnItem()
    /// \brief ajoute un objet récolté

    void gainAnItem();


    /// \fn void loseAnItem()
    /// \brief enlève un objet

    void loseAnItem();

    /// \fn void resetItem()
    /// \brief ajoute un item récolté

    void resetItem();
    

    /// \fn void resetSpeed()
    /// \brief intitalise la vitesse actuelle à la vitesse de base

    void resetSpeed();


    /// \fn void resetJumpH()
    /// \brief intitalise la hauteur de saut actuelle à la hauteur de saut de base

    void resetJumpH();


    /// \fn void loseALife()
    /// \brief enlève une vie 

    void loseALife();
    
    
    /// \fn void gainALife()
    /// \brief ajoute une vie

    void gainALife();


    /// \fn void winRound()
    /// \brief intialise la variable win à true (1)

    void winRound();


    /// \fn void moveRight()
    /// \brief déplace le joueur vers la droite

    void moveRight();


    /// \fn void moveLeft()
    /// \brief déplace le joueur vers la gauche

    void moveLeft();


    /// \fn void jump()
    /// \brief deplace le joueur dans les airs

    void refreshJump();


    /// \fn void refreshHitbox()
    /// \brief actualise les hitbox avec les positions

    void refreshHitbox();

    
    /// \fn void gravity(SDL_Rect& sol)
    /// \brief fait tomber le joueur quand il n'est pas sur un plateforme

    void gravity(const SDL_Rect* tab);

    /// \fn void setPosRel()
    /// \brief set la position relative cad celle qui prevoit la hauteur du saut 

    void setPosRel();

    /// \fn int whereHitboxTouch()
    /// \brief Renvoie un entier en fonction de quel côté touche le personnage

    void refreshMovement();

    void gravity(const vector<SDL_Rect> &tab_plateform);

    runner operator=(const runner & r);

    void reset(unsigned int x, unsigned int y);
};

#endif