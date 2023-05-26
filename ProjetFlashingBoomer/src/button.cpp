#include "button.h"

button::button():

    posXJouer(384),  // positionX pour être à la moitié de l'écran sur un écran 1920 x 1080:
                // 1920/2 - (largeur) 300/2
    posYJouer(570),  // positionY pour être au 2/3 de l'écran sur un écran 1920 x 1080:
                // 2/3 * 1080 - (hauteur) 300/2
    WidthJouer(384), // 1920/5
    HeightJouer(384),

    posXQuit(1152),
    posYQuit(570),
    WidthQuit(384),
    HeightQuit(384),

    hitboxRectInit {0, 0, 128, 128},
    hitboxRectJouer {int(posXJouer), int(posYJouer), int(WidthJouer), int(HeightJouer)},
    hitboxRectQuit {int(posXQuit), int(posYQuit), int(WidthQuit), int(HeightQuit)},

    spriteJouer(IMG_Load("data/Jouer.png")),
    spriteQuit(IMG_Load("data/quit.png"))
{}

button::button(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2):
    posXJouer(x1),
    posYJouer(y1),
    WidthJouer(384),
    HeightJouer(384),

    posXQuit(x2),
    posYQuit(y2),
    WidthQuit(384),
    HeightQuit(384),

    hitboxRectInit{0, 0, 128, 128},
    hitboxRectJouer {int(posXJouer), int(posYJouer), 384, 384},
    hitboxRectQuit {int(posXQuit), int(posYQuit), 384, 384},

    spriteJouer(IMG_Load("data/Jouer.png")),
    spriteQuit(IMG_Load("data/quit.png"))
{}

button::~button()
{
    SDL_FreeSurface(spriteJouer);
    SDL_FreeSurface(spriteQuit);
}

unsigned int button::getposXJouer() const
{
    return posXJouer;
}

void button::setposXJouer(unsigned int value)
{
    posXJouer = value;
}

unsigned int button::getposYJouer() const
{
    return posYJouer;
}

void button::setposYJouer(unsigned int value)
{
    posYJouer = value;
}

unsigned int button::getwidthJouer() const
{
    return hitboxRectJouer.w;
}

void button::setwidthJouer(unsigned int value)
{
    WidthJouer = value;
}

unsigned int button::getheightJouer() const
{
    return hitboxRectJouer.h;
}

void button::setheightJouer(unsigned int value)
{
    HeightJouer = value;
}

unsigned int button::getposXQuit() const
{
    return posXQuit;
}

void button::setposXQuit(unsigned int value)
{
    posXQuit = value;
}

unsigned int button::getposYQuit() const
{
    return posYQuit;
}

void button::setposYQuit(unsigned int value)
{
    posYQuit = value;
}

unsigned int button::getwidthQuit() const
{
    return WidthQuit;
}

void button::setwidthQuit(unsigned int value)
{
    WidthQuit = value;
}

unsigned int button::getheightQuit() const
{
    return HeightQuit;
}

void button::setheightQuit(unsigned int value)
{
    HeightQuit = value;
}


SDL_Surface* button::getSpriteJouer() const
{
    return spriteJouer;
}

SDL_Surface* button::getSpriteQuit() const
{
    return spriteQuit;
}

SDL_Rect& button::getHitboxRectJouer()
{
    return hitboxRectJouer;
}

SDL_Rect& button::getHitboxRectQuit()
{
    return hitboxRectQuit;
}

void button::setHitboxRectJouer(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    SDL_Rect newhitbox{int(x), int(y), int(w), int(h)};
    hitboxRectJouer = newhitbox;
}

void button::setHitboxRectQuit(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    SDL_Rect newhitbox{int(x), int(y), int(w), int(h)};
    hitboxRectQuit = newhitbox;
}


SDL_Rect& button::getHitboxRectInit()
{
    return hitboxRectInit;
}