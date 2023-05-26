#ifndef _GAME_H_
#define _GAME_H_

#ifndef PI
#define PI 3.14159265
#endif

/// \file game.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
//#include <SDL2/SDL_ttf.h>

#include "runner.h"
#include "timer.h"
#include "map.h"
#include "canon.h"
#include "weapon.h"
#include "button.h"
#include "menu.h"
#include "coin.h"
#include "hud.h"
#include "heart.h"

#include <math.h>
#include <iostream>
using namespace std;

/// \class game
/// \brief classe gerant les instances du jeu tels que les boucles d'evenements, les personnages, la carte, etc...

class game
{
private:

    float ratio;
    float Width, Height;
    unsigned int PosXButtonJouer, PosYButtonJouer, PosXButtonQuit, PosYButtonQuit, SquareSizeButton;
    unsigned int NbCoinsCollected;  ///le nombre de pieces collectées
    
public:
    float x,y;

    SDL_DisplayMode DM;

    SDL_Window* window; ///la fenetre SDL
    SDL_Renderer* renderer; ///le rendu SDL
    SDL_Event events;   ///evenements utilisateur

    runner Runner;    ///le runner
    SDL_Texture* textureRunner; ///contient la conversion des sprite (surface) de runner en texture

    canon Canon;    ///le Canon
    SDL_Texture* textureCanon;  ///contient les sprite du canon

    int scoreRunner;    ///le score du Runner
    int scoreCanon; ///le score du Canon

    menu Menu;  ///une instance de menu
    SDL_Texture* textureMenu;   ///l'image du menu
    bool dansLeMenu;    ///permet de savoir si on se situe actuellement dans le menu ou en jeu

    button Button;
    SDL_Texture* textureButtonJouer;
    SDL_Texture* textureButtonQuit;

    timer TimerRunner;    //un timer capable de renvoyer le temps passer depuis un certain moment
    timer TimerCoin;

    map Map;    ///la carte et tous ses elements
    SDL_Texture* textureBackground; ///le fond 

    string mapList[3];

    SDL_Texture* textureWeapon;
    SDL_Texture* textureBullet;
    

    coin Coin; //la pièce et tous ses elements
    SDL_Texture* textureCoinMap;

    heart Heart;
    SDL_Texture* textureHeartMap;

    hud Hud;
    SDL_Texture* textureCoinHud;
    SDL_Texture* textureHeartHud;

    SDL_Texture* textureRunnerWinScreen;
    SDL_Texture* textureCanonWinScreen;

    SDL_Texture* textureRunnerWinTheGame;
    SDL_Texture* textureCanonWinTheGame;
    SDL_Texture* textureItsADrawScreen;


    //TTF_Font *font1;


    /// \fn game()
    /// \brief constructeur par defaut de la classe

    game();


    /// \fn ~game()
    /// \brief destructeur par defaut de la classe

    ~game();

//----------------------------INITIALISATIONS----------------------------------------

    /// \fn int init_SDL()
    /// \brief démarrage des extensions SDL

    int init_SDL();


    /// \fn int init_WinRenTex()
    /// \brief initialisation de la fenetre, rendu, et textures

    int init_WinRenTex();  


    /// \fn void destroyAndQuitSDL()
    /// \brief liberation de la memoire prise par SDL

    void destroyAndQuitSDL();

    void createMapElement(string mapFilename);

//------------------------------EVENEMENTS---------------------------------------

    /// \fn void keysDownForRunnerMovements(const SDL_Keycode& leftKey, const SDL_Keycode& rightKey, const SDL_Keycode& upKey)
    /// \brief la gestion des touches (lors de l'appuie) pour les mouvements du Runner

    void keysDownForRunnerMovements(const SDL_Keycode& leftKey, const SDL_Keycode& rightKey, const SDL_Keycode& upKey);

    /// \fn void keysUpForRunnerMovements(const SDL_Keycode& leftKey, const SDL_Keycode& rightKey);
    /// \brief la gestion des touches (a la fin de l'appuie) pour les mouvements du Runner
    
    void keysUpForRunnerMovements(const SDL_Keycode& leftKey, const SDL_Keycode& rightKey);


    /// \fn float angleBetweenHorizonAndMouse()
    /// \brief calcule l'angle entre la postition de la souris et la droite horizontale passant par le centre du canon

    float angleBetweenHorizonAndMouse();


    /// \fn float angleBetweenHorizonAndMouse()
    /// \brief calcule l'angle entre la postition de la souris et la droite horizontale passant par le centre du canon
    
    void canonRotationWithMouse();


    /// \fn void refreshProjectileState()
    /// \brief gere la suppression des projectiles 

    void refreshProjectileState();   //la gestion des projectiles lors de leur explosion

    
    /// \fn bool eventLoop()
    /// \brief la boucle de tous les evenements

    bool eventLoop();

    /// \fn bool menuLoop()
    /// \brief la boucle des evenements du menu

    bool menuLoop();

    /// \fn bool gameLoop()
    /// \brief la boucle de tous les evenements du jeu

    int testWinner();

    /// \fn bool playLoop()
    /// \brief la boucle de tous les evenements du jeu

    bool playLoop();

    void refreshGame();

    void resetRound(int roundNb);
//---------------------------------FONCTIONS D'AFFICHAGE-------------------------------------------------
    /// \fn InitRatioWindow()
    /// \brief définit le ratio de la taille de l'écran, pour pouvoir l'utiliser dans nos coordonnées

    void InitRatioWindow();

    /// \fn InitRatioCoordinates()
    /// \brief définit les coordonnées de l'écran, en fonction du ratio

    void InitCoordinates();

    void AfficherTest(); // fonction pour afficher tout ce dont on a besoin de tester. A supprimer

    /// \fn void drawLinesRunner()
    /// \brief dessine les lignes autour du coureur (dans le but de voir de quel côté le coureur touche une plateforme)

    void drawLinesRunner();

    /// \fn void drawRectPlateforms(SDL_Rect *t)
    /// \brief affiche les plateformes de la map en fonction du tableau de rectangles passé en paramètre
    /// \param t Tableau de rectangles

    void drawRectPlateforms();

    /// \fn void drawRectWalls(SDL_Rect *t)
    /// \brief affiche les murs de la map en fonction du tableau de rectangles passé en paramètre
    /// \param t Tableau de rectangles

    void drawRectWalls(SDL_Rect* t);

    /// \fn void drawCanon()
    /// \brief dessine le canon et son arme sur la map

    void drawCanon();

    /// \fn void drawnProjectiles()
    /// \brief dessine les projectiles sur la map

    void drawProjectiles();

    /// \fn void displayMenu()
    /// \brief actualise l'affichage du rendu lorsque l'on se toruve dans le menu
    void displayMenu(); //je teste deux différentes display que j'appelle suivant les évents

    /// \fn void displayMap()
    /// \brief actualise l'affichage du rendu lorsque l'on se toruve dans le jeu
    void displayMap(); // ce display, c'est notre "ancien principal, celui du runner donc"

    void displayAll();


    /// \fn void drawMap()
    /// \brief affiche une texture map intialisée dans la classe map

    void drawMap();

    /// \fn void drawMenu()
    /// \brief affiche une texture menu intialisée dans la classe menu
    void drawMenu();

    /// \fn void drawHud()
    /// \brief affiche le Hud sur la map
    void drawHud();
    
    /// \fn void drawCoinsMap()
    /// \brief affiche les pièces correspondant aux coordonnées du tableau de pièces passé paramètre, compte également le nb de pièces restantes et le nb de points du runner
    void drawCoinsMap();

    /// \fn void drawCoinsHud()
    /// \brief affiche les pièces correspondant aux coordonnées du tableau de pièces passé paramètre, compte également le nb de pièces restantes et le nb de points du runner
    void drawCoinsHud();

    /// \fn void drawHeartHud()
    /// \brief affiche les coeurs correspondant aux coordonnées du tableau de coeurs passé en paramètre
    void drawHeartHud();

    /// \fn void InteractRunnerCoins()
    /// \brief modfie la valeur du booléen CoinOnMap si il y a interaction entre le runner et une pièce
    void InteractRunnerCoins(); 

    void InteractRunnerHeart();

    /// \fn void CountItemsCollected()
    /// \brief Compte le nombre de pièces ramassées et met ce nombre dans la variable NbItemsCollected
    void CountItemsCollected();

    /// \fn void EventsLife()
    /// \brief Tous les événements liés aux vies du runner
    void EventsLife();

//---------------------ANIMATIONS----------------

    /// \fn staticRunnerAnimation()
    /// \brief une serie de test qui determine le sprite du Runner a utiliser afin de l'animer

    void staticRunnerAnimation();


    /// \fn runningRunnerAnimation()
    /// \brief determine le sprite du Runner a utiliser lors de la course

    void runningRunnerAnimation();
    
    /// \fn canonRotationAnimation()
    /// \brief determine le sprite de l'arme a utiliser lors de la rotation du canon

    void canonRotationAnimation();

    /// \fn staticCoinAnimation()
    /// \brief une serie de test qui determine le sprite de la pièce a utiliser afin de l'animer (tourner sur elle-même)

    void staticCoinAnimation();

    //void staticCoinAnimationv2();



    
};




#endif