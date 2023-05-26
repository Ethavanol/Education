#include "runner.h"
#include "tweening.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

runner::runner():   

    life(3),
    nbItem(0),

    baseSpeed(10),
    baseJumpH(250),
    jumpSpeed(20),

    speed(baseSpeed),
    jumpH(baseJumpH),

    absPosX(0),
    absPosY(0),
    relPosX(absPosX),
    relPosY(absPosY),

    Width(128),
    Height(128),

    isMoving(false),
    isGoingLeft(false),
    isGoingRight(false),
    isJumping(false),
    isTouchingGround(false),

    sprite(IMG_Load("data/runner_spritev9.png")),
    hitboxRect {int(absPosX), int(absPosY), int(Width), int(Height)}, //a modifier quand sprite animé
    hitboxRectRel{int(absPosX), int(absPosY), int(Width), int(Height)}

{
    srcRectSprite = new SDL_Rect[16] {{0, 0, 32, 32}, {32, 0, 32, 32}, //ligne de sprite 1 [0], [1]
                                    {0, 32, 32, 32}, {32, 32, 32, 32}, {64, 32, 32, 32}, {96, 32, 32, 32}, {128, 32, 32, 32}, {160, 32, 32, 32},   //ligne de sprite 2 [2], [3], [4], [5], [6], [7]
                                    {0, 64, 32, 32}, {32, 64, 32, 32},  //ligne de sprite 3 [8], [9]
                                    {0, 96, 32, 32}, {32, 96, 32, 32}, {64, 96, 32, 32}, {96, 96, 32, 32}, {128, 96, 32, 32}, {160, 96, 32, 32}};   //ligne de sprite 4 [10], [11], [12], [13], [14], [15]
    selectedSpriteFrame = 0;
    currentSpriteFrame = srcRectSprite[0];
}

runner::runner(unsigned int x, unsigned int y, unsigned int w, unsigned int h):   

    life(3),
    nbItem(0),

    baseSpeed(10),
    baseJumpH(200),
    jumpSpeed(20),

    speed(baseSpeed),
    jumpH(baseJumpH),

    absPosX(x),
    absPosY(y),
    relPosX(absPosX),
    relPosY(absPosY),

    Width(w),
    Height(h),

    isMoving(false),
    isGoingLeft(false),
    isGoingRight(false),
    isJumping(false),
    isTouchingGround(false),

    sprite(IMG_Load("data/runner_spritev9.png")),
    hitboxRect {int(absPosX), int(absPosY), int(Width), int(Height)}, //a modifier quand sprite animé
    hitboxRectRel{int(absPosX), int(absPosY), int(Width), int(Height)}

{
    srcRectSprite = new SDL_Rect[16] {{0, 0, 32, 32}, {32, 0, 32, 32}, //ligne de sprite 1 [0], [1]
                                    {0, 32, 32, 32}, {32, 32, 32, 32}, {64, 32, 32, 32}, {96, 32, 32, 32}, {128, 32, 32, 32}, {160, 32, 32, 32},   //ligne de sprite 2 [2], [3], [4], [5], [6], [7]
                                    {0, 64, 32, 32}, {32, 64, 32, 32},  //ligne de sprite 3 [8], [9]
                                    {0, 96, 32, 32}, {32, 96, 32, 32}, {64, 96, 32, 32}, {96, 96, 32, 32}, {128, 96, 32, 32}, {160, 96, 32, 32}};   //ligne de sprite 4 [10], [11], [12], [13], [14], [15]
    currentSpriteFrame = srcRectSprite[0];
}

runner::~runner()
{
    SDL_FreeSurface(sprite);
    delete [] srcRectSprite;
    srcRectSprite = NULL;
}   


//ACCESSEUR ET MUTATEUR (par ordre de variable)

unsigned int runner::getLife() const
{
    return life;
}

void runner::setLife(unsigned int value)
{
    life = value;
}

unsigned int runner::getNbItem() const
{
    return nbItem;
}

void runner::setNbItem(unsigned int value)
{
    nbItem = value;
}

bool runner::getWin() const
{
    return win;
}

void runner::setWin(bool value)
{
    win = value;
}

unsigned int runner::getBaseSpeed() const
{
    return baseSpeed;
}

int runner::getSpeed() const
{
    return speed;
}

void runner::setSpeed(int value)
{
    speed = value;
}

unsigned int runner::getJumpH() const
{
    return jumpH;
}

void runner::setJumpH(unsigned int value)
{
    jumpH = value;
}

unsigned int runner::getAbsPosX() const
{
    return absPosX;
}

void runner::setAbsPosX(unsigned int value)
{
    absPosX = value;
}

unsigned int runner::getAbsPosY() const
{
    return absPosY;
}

void runner::setAbsPosY(unsigned int value)
{
    absPosY = value;
}

unsigned int runner::getRelPosX() const
{
    return relPosX;
}

void runner::setRelPosX(unsigned int value)
{
    relPosX = value;
}

unsigned int runner::getRelPosY() const
{
    return relPosY;
}

void runner::setRelPosY(unsigned int value)
{
    relPosY = value;
}

SDL_Surface* runner::getSprite() const
{
    return sprite;
}

SDL_Rect& runner::getHitboxRect() 
{
    return hitboxRect;
}

SDL_Rect& runner::getHitboxRelRect()
{
    return hitboxRectRel;
}

SDL_Rect& runner::getCurrentSpriteFrame()
{
    return currentSpriteFrame;
}

void runner::setCurrentSpriteFrame(const SDL_Rect& value)
{
    currentSpriteFrame = value;
}

int runner::getSelectedSpriteFrame() const
{
    return selectedSpriteFrame;
}

void runner::setSelectedSpriteFrame(const int& value)
{
    selectedSpriteFrame = value;
}

bool runner::getIsMoving() const
{
    return isMoving;
}

void runner::setIsMoving(const bool& value)
{
    isMoving = value;
}

bool runner::getIsJumping() const
{
    return isJumping;
}

void runner::setIsJumping(const bool& value)
{
    isJumping = value;
}

bool runner::getIsTouchingGround() const
{
    return isTouchingGround;
}

void runner::setIsTouchingGround(const bool& value)
{
    isTouchingGround = value;
}

bool runner::getIsGoingLeft() const
{
    return isGoingLeft;
}

void runner::setIsGoingLeft(const bool& value)
{
    isGoingLeft = value;
}

bool runner::getIsGoingRight() const
{
    return isGoingRight;
}

void runner::setIsGoingRight(const bool& value)
{
    isGoingRight = value;
}

//FONCTION ET PROCEDURES RACCOURCIES

void runner::gainAnItem()
{
    nbItem++;
}

void runner::loseAnItem()
{
    nbItem--;
}

void runner::resetItem()
{
    nbItem = 0;
}

void runner::resetSpeed()
{
    speed = baseSpeed;
}

void runner::resetJumpH()
{
    jumpH = baseJumpH;
}

void runner::loseALife()
{
    life--;
}

void runner::gainALife()
{
    life++;
}

void runner::winRound()
{
    win = true;
}

void runner::moveRight()
{
    absPosX += speed;
    hitboxRect.x = absPosX;
    setPosRel();
    refreshHitbox();
}

void runner::moveLeft()
{
    absPosX -= speed;
    hitboxRect.x = absPosX;
    setPosRel();
    refreshHitbox();
}


void runner::refreshJump()
{
    if(getIsJumping())  //le saut a demarré 
    {
        if(!getIsTouchingGround())  //si on ne touche pas le sol
        {
            absPosY -= jumpSpeed;   //on continue l'ascension 
            refreshHitbox();
        }
        else
        {
            setPosRel();    //sinon on demarre le saut
            absPosY -= jumpSpeed;

            refreshHitbox();
        }

        if(absPosY <= relPosY)  //si on atteint la hauteur de saut désirée
        {
            absPosY = relPosY;
            setIsJumping(false);    //le saut est fini
            refreshHitbox();
        }
    }

}


void runner::refreshHitbox()    //actualise les hitbox
{
    hitboxRect.x = absPosX;
    hitboxRect.y = absPosY;
    hitboxRectRel.x = relPosX;
    hitboxRectRel.y = relPosY;
    hitboxRect.w = Width;
    hitboxRect.h = Height;
    hitboxRectRel.w = Width;
    hitboxRectRel.h = Height;

}


void runner::setPosRel()    //set la position relative du saut 
{
    if(isTouchingGround)
    {
        relPosX = absPosX;
        relPosY = absPosY - jumpH;
    }

}


void runner::refreshMovement()
{

    if(isGoingRight)    //... ET qu'on va a droite
    {
       moveRight();
    }

    else if(isGoingLeft)   //... ET qu'on va a gauche (mais pas a droite)
    {
        moveLeft();
    }
}


void runner::gravity(const vector<SDL_Rect> &tab_plateform)
{
    for(int i = 0; i < tab_plateform.size(); i++)  //on test toutes les plateformes
    {
        if(SDL_HasIntersection(&hitboxRect, &tab_plateform[i])) //si on touche une plateforme...
        {
            if(int(tab_plateform[i].y + tab_plateform[i].h) >= int(absPosY + hitboxRect.h)) //... ET la position des pieds du runner est superieur a la plateforme 
            {
                if(getIsJumping())  //... si on est en plain saut
                {
                    setIsTouchingGround(false); // on ne cosidere pas qu'on touche le sol
                }
                else
                {
                    setIsTouchingGround(true);  //sinon oui
                }
                

                break;  
            }
            else    //... ET si la position du joueur n'est pas au dessus de la palteforme
            {
                setIsTouchingGround(false); //on n'est pas en train de toucher le sol
            }
        }
        else    //si on ne touche pas de palteforme
        {
            setIsTouchingGround(false); //on n'est pas en train de toucher le sol
        }
    }

    if(!getIsTouchingGround() && !getIsJumping())   //si on touchne touche pas le sol ET qu'on ne saute pas...
    {
        absPosY += 9;   //la gravité fait son effet
        //setPosRel();
        refreshHitbox();    //on rafraichit les hitbox 
    }

}

void runner::reset(unsigned int x, unsigned int y)
{
    life = 3;
    nbItem = 0;


    absPosX = x;
    absPosY = y;
    relPosX = absPosX;
    relPosY = absPosY;

    isMoving = false;
    isGoingLeft = false;
    isGoingRight = false;
    isJumping = false;
    isTouchingGround = false;
}