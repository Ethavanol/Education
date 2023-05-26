#include "game.h"
#include "runner.h"
#include "map.h"
#include "weapon.h"

game::game():

    ratio(0),
    PosXButtonJouer(384),
    PosYButtonJouer(570),
    PosXButtonQuit(1152),
    PosYButtonQuit(570),
    //W(300),
    //H(300),
    window {nullptr},
    renderer {nullptr},
    //RectWritingZone{500, 300, 300, 300},
    Canon(500, 500),
    Button(PosXButtonJouer, PosYButtonJouer, PosXButtonQuit, PosYButtonQuit)
    
    // police {NULL}
{
    dansLeMenu = true;
    //font1 = TTF_OpenFont("/home/ethan/.local/share/Trash/files/Arimo-Bold.7.ttf", 50 ); 

    mapList[0] = "data/mapfile.txt";
    mapList[1] = "data/mapfile2.txt";
    mapList[2] = "data/mapfile3.txt";
}


game::~game()
{
    destroyAndQuitSDL();
}

//----------------------------INITIALISATIONS----------------------------------------

int game::init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)   //initialisation et test de la SDL
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    if (IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) < 0)    //initialisation de la gestion des formats d'images
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
/*
    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
        return EXIT_FAILURE; 
    }
    return EXIT_SUCCESS;*/
}

int game::init_WinRenTex()
{
    window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080 , SDL_WINDOW_SHOWN);  //creation de la fenetre
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if(window < 0)  //test de l'initialisation de la fenetre
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    //creation du rendu

    if(renderer < 0)    //test de l'initialisation du rendu
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "GAME");    //titre de la fenetre

    textureRunner = SDL_CreateTextureFromSurface(renderer, Runner.getSprite()); //conversion des surfaces sprite en textures
    
    textureButtonJouer = SDL_CreateTextureFromSurface(renderer, Button.getSpriteJouer());
    textureButtonQuit = SDL_CreateTextureFromSurface(renderer, Button.getSpriteQuit());
    textureBackground = SDL_CreateTextureFromSurface(renderer, Map.background);

    textureMenu = SDL_CreateTextureFromSurface(renderer, Menu.backgroundMenu);
    textureCoinMap = SDL_CreateTextureFromSurface(renderer, Map.getSpriteCoinMap());
    textureCoinHud = SDL_CreateTextureFromSurface(renderer, Hud.getSpriteCoinHud());
    textureHeartHud = SDL_CreateTextureFromSurface(renderer, Hud.getSpriteHeartHud());
    textureHeartMap = SDL_CreateTextureFromSurface(renderer, Map.getSpriteHeartMap());
   // textureWritingLives = SDL_CreateTextureFromSurface(renderer, Hud.getWritingLives());
    //SDL_QueryTexture(textureWritingLives, NULL, NULL, &W, &H);
    textureCanon = SDL_CreateTextureFromSurface(renderer, Canon.getSprite());
    textureWeapon = SDL_CreateTextureFromSurface(renderer, Canon.Weapon.getSprite());

    textureBullet = SDL_CreateTextureFromSurface(renderer, Canon.Weapon.getProjectileSprite());


    //SDL_Surface* rWinScreen = IMG_Load("data/runnerWin.png");
    textureRunnerWinScreen = SDL_CreateTextureFromSurface(renderer, IMG_Load("data/runnerWin.png"));
    //SDL_FreeSurface(rWinScreen);

    //SDL_Surface* cWinScreen = IMG_Load("data/canonWin.png");
    textureCanonWinScreen = SDL_CreateTextureFromSurface(renderer, IMG_Load("data/canonWin.png"));

    
    textureRunnerWinTheGame = SDL_CreateTextureFromSurface(renderer, IMG_Load("data/runnerWinTheGame.png"));
    textureCanonWinTheGame = SDL_CreateTextureFromSurface(renderer, IMG_Load("data/canonWinTheGame.png"));
    textureItsADrawScreen = SDL_CreateTextureFromSurface(renderer, IMG_Load("data/itsADraw.png"));

    InitRatioWindow();
    InitCoordinates();
    //Map.ListPlatforms2();
    //Map.InitListCoinsMap(); // on appelle la fonction qui permet d'initialiser les coordonnées de la liste
    // de pièce

    return EXIT_SUCCESS;
}


void game::destroyAndQuitSDL()  //libere la memoire
{
    SDL_DestroyTexture(textureRunner);
    SDL_DestroyTexture(textureCanon);

    SDL_DestroyTexture(textureBackground);
    SDL_DestroyTexture(textureWeapon);
    SDL_DestroyTexture(textureBullet);

    SDL_DestroyTexture(textureButtonJouer);
    SDL_DestroyTexture(textureButtonQuit);
    SDL_DestroyTexture(textureMenu);
    SDL_DestroyTexture(textureCoinMap);
    SDL_DestroyTexture(textureCoinHud);
    SDL_DestroyTexture(textureHeartHud);
    SDL_DestroyTexture(textureHeartMap);

    SDL_DestroyTexture(textureRunnerWinScreen);
    SDL_DestroyTexture(textureCanonWinScreen);

    SDL_DestroyTexture(textureRunnerWinTheGame);
    SDL_DestroyTexture(textureCanonWinTheGame);
    SDL_DestroyTexture(textureItsADrawScreen);

    //SDL_DestroyTexture(textureWritingLives);
    //TTF_CloseFont(font1);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void game::createMapElement(string mapFilename) //positionne les elements sur la carte 
{
    SDL_GetCurrentDisplayMode(0, &DM); // ça j'ai pas trop cherché à comprendre pour l'instant
    Width = DM.w; // ça ça renvoie la largeur de l'écran de la machine sur laquelle on éxécute
    Height = DM.h; // ça ça renvoie la hauteur de l'écran de la machine sur laquelle on éxécute

    Map.readMapFile(Width, Height, mapFilename);
    
    for(int i = 0; i < Hud.getSizelistCoin(); i++)
    {
        Hud.listCoinScore[i].setIsCollected(false);

    }

    Runner.setAbsPosX(Map.runnerSpawnPoint.x);
    Runner.setAbsPosY(Map.runnerSpawnPoint.y);
    Runner.setWidth(Width/16);
    Runner.setHeight(Height/9);
    //faire une fonction runner reset pour tout remettre par default au debut de la manche

    /*Runner.setAbsPosX(Map.runnerSpawnPoint.x);
    Runner.setAbsPosY(Map.runnerSpawnPoint.y);*/
    Runner.reset(Map.runnerSpawnPoint.x, Map.runnerSpawnPoint.y);

    /*Canon.setPosX(Map.canonSpawnPoint.x);
    Canon.setPosY(Map.canonSpawnPoint.y);*/
    Canon.reset(Map.canonSpawnPoint.x, Map.canonSpawnPoint.y);

    Canon.refreshPosition();
    //idem pour le canon

    Heart.setHeartPosX(Map.heartSpawnRect.x);
    Heart.setHeartPosY(Map.heartSpawnRect.y);
    Heart.setHeartWidth(Map.heartSpawnRect.w);
    Heart.setHeartHeight(Map.heartSpawnRect.h);
    Heart.refreshHitboxHeart();
}

//------------------------------EVENEMENTS---------------------------------------

void game::InitRatioWindow() // ici, on définit le ratio de la fenêtre sur celle d'une de 1920 * 1080
{   //le but c'est de définir le ratio dès le début pour pouvoir l'utiliser partout
    SDL_GetCurrentDisplayMode(0, &DM); // ça j'ai pas trop cherché à comprendre pour l'instant
    Width = DM.w; // ça ça renvoie la largeur de l'écran de la machine sur laquelle on éxécute
    Height = DM.h; // ça ça renvoie la hauteur de l'écran de la machine sur laquelle on éxécute
    ratio = Width/1920; // ça ça fait le ratio de la longueur de la machine sur 1920, c'est-à-dire, la machine de base
    //(on aurait pu faire avec la hauteur ça donne le même résultat)
}

void game::InitCoordinates()//Ici on redéfinit les variables avec le ratio, par exemple, la positionX
// de l'image du bouton, pour qu'on puisse s'en servir dans tout le code.
//possibilité d'amélioration en mettant un "if (ratio == 1)" pour éviter toutes les recoordonnées
{
    SquareSizeButton = ((1920*ratio)/5);
    Button.setposXJouer((1920*ratio)/5); // On prend la longueur de l'écran qu'on
    // divise par deux  (donc à la moitié), ensuite on retire la moitié de la largeur du bouton
    Button.setposYJouer(((2160*ratio)/3) - (SquareSizeButton/2)); // comme on veut 2/3 de la hauteur, on fait:
    // 2 x 1080 x ratio , le tout divisé par 3. On retire la moitié de la hauteur du bouton également
    Button.setwidthJouer(SquareSizeButton);
    Button.setheightJouer(SquareSizeButton);

    Button.setposXQuit((3*1920*ratio)/5);
    Button.setposYQuit(((2160*ratio)/3) - (SquareSizeButton/2));
    Button.setwidthQuit(SquareSizeButton);
    Button.setheightQuit(SquareSizeButton);


    Button.setHitboxRectJouer(Button.getposXJouer(), Button.getposYJouer(), SquareSizeButton, SquareSizeButton);
    Button.setHitboxRectQuit(Button.getposXQuit(), Button.getposYQuit(), SquareSizeButton, SquareSizeButton);

    for(unsigned int i=0; i<Hud.getSizelistCoin(); i++)
    {
        Hud.listCoinScore[i].setCoinPosX(Width - 200 + 40*i); //e, gros on veut afficher 5 pièces en haut
        //à droite. On les veut à côté et sur la même ligen, donc tout d'abord pour y on assigne
        //la même valeur à toutes les pièces du tablau. En suite, on veut que les pièces soient affichées
        //avec 40 d'écart, presque collée à droite. la dernière sera donc à largeur - 40, l'avant-dernière
        //à largeur - 80 et ainsi de suite
        Hud.listCoinScore[i].setCoinPosY(48);
    }

    for(unsigned int j=0; j<Hud.getSizelistHeart(); j++)
    {
        Hud.listHeart[j].setHeartPosX(Width - 40*(j+1)); // même méthode qu'au-dessus, mais ici on a que
        // 3 coeurs
        Hud.listHeart[j].setHeartPosY(8);
    }

}

void game::AfficherTest() // fonction qui a pour but d'afficher tous les trucs à tester
{
    cout << "Ratio : "<< ratio << endl;
    cout << "Pos x: " << PosXButtonJouer << " Pos Y: " << PosYButtonJouer << endl;
    cout << "Pos x Q : " << PosXButtonQuit << " Pos Y: " << PosYButtonQuit << endl;

}


void game::keysDownForRunnerMovements(const SDL_Keycode& leftKey, const SDL_Keycode& rightKey, const SDL_Keycode& upKey)    //les evenements des touches de mouvements droite et gauche et de saut du runner(KEYDOWN)
{
    //DROITE
    if(!Runner.getIsGoingRight())   //si on est pas deja en train d'aller a droite...
    {
        if(events.key.keysym.sym == rightKey && !Runner.getIsGoingLeft()) //appui fleche droite...
        {
            //on initialise le premier sprite
            Runner.setSelectedSpriteFrame(2);
                        
            Runner.setIsMoving(true);   //on se met en mouvement...
            Runner.setIsGoingRight(true);   //... vers la droite.
            Runner.setIsGoingLeft(false);   //si on va a droite, on ne va plus a gauche
        }
    }
    //GAUCHE
    if(!Runner.getIsGoingLeft())    //si on est pas deja en train d'aller a gauche...
    {
        if(events.key.keysym.sym == leftKey && !Runner.getIsGoingRight())  //...ET qu'on appui sur la touche...
        {
            //on initialise le premier sprite
            Runner.setSelectedSpriteFrame(10);

            Runner.setIsMoving(true);   //on se met en mouvement...
            Runner.setIsGoingLeft(true);    //... vers la gauche.
            Runner.setIsGoingRight(false);  //si on va a gauche, on ne va plus a droite
        }
    }

    //SAUT
    if(Runner.getIsTouchingGround())    //si on touche le sol ...
    {
        if(events.key.keysym.sym == upKey)    //... ET appui fleche haut
        {                    
            Runner.setIsJumping(true);  //on demarre le saut
        }
    }
}

void game::keysUpForRunnerMovements(const SDL_Keycode& leftKey, const SDL_Keycode& rightKey)    //les evenements des touches de mouvements droite et gauche et de saut du runner(KEYDOWN)
{
    if(events.key.keysym.sym == rightKey) //fin appui fleche droite ou gauche 
    {
        Runner.setIsGoingRight(false);
        Runner.setIsMoving(false);

        if(!Runner.getIsGoingLeft())    //initialisation du sprite a l'arret
        {
            Runner.setSelectedSpriteFrame(0);
        }
    }

    if(events.key.keysym.sym == leftKey) //fin appui fleche droite ou gauche 
    {
        Runner.setIsGoingLeft(false);
        Runner.setIsMoving(false);
                    
        if(!Runner.getIsGoingRight())   //initialisation du sprite a l'arret
        {
            Runner.setSelectedSpriteFrame(8);
        }
    }
}

float game::angleBetweenHorizonAndMouse()
{
    int centerCanonX = Canon.getPosX() + int(Canon.getHitboxRect().w/2);    //coordonnées du centre du canon selon les abscisses
    int centerCanonY = Canon.getPosY() + int(Canon.getHitboxRect().h/2);    //coordonnées du centre du canon selon les ordonnées

    
    if(centerCanonY >= int(events.motion.y)) //si on est au dessus du canon
    {
        return atan2(centerCanonY - events.motion.y, events.motion.x - centerCanonX);
    }
    else     //si on est en dessous
    {
       return 2*PI + atan2(centerCanonY - events.motion.y, events.motion.x - centerCanonX);
    }

}

void game::canonRotationWithMouse()
{
    Canon.setAngle(angleBetweenHorizonAndMouse());
    Canon.refreshAngles();
}


void game::refreshProjectileState() //permet de savoir si le projectile a touche un obstacle (ou (temporaire) a quitté la carte)
{
    for(int i = 0; i < int(Canon.Weapon.arrBullet.size()); i++)
    {
        Canon.Weapon.arrBullet[i].refreshExplosion(Runner);


        SDL_Rect windowBox = {0, 0, SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h};
        
        if(!SDL_HasIntersection(&windowBox, &Canon.Weapon.arrBullet[i].getHitbox()))
        {
            Canon.Weapon.arrBullet[i].setDetonate(true);
            Canon.Weapon.arrBullet[i].setIsMoving(false);
        }
}
    }


bool game::eventLoop()
{
    //while (SDL_PollEvent(&events))  //tant qu'on "entend" des evenements
    //{
        //menuLoop();

        switch (events.type)    //test de l'evenement entendu
        {
            case SDL_WINDOWEVENT:   //fermeture fenetre
            if(events.window.event == SDL_WINDOWEVENT_CLOSE)
                return false;
            break;

            case SDL_KEYDOWN:   //a l'appui d'une touche

            if (events.key.keysym.sym == SDLK_ESCAPE) //fermeture de la fenêtre si on appui sur échap
            {
                return false;
            }
                
            keysDownForRunnerMovements(SDLK_LEFT, SDLK_RIGHT, SDLK_UP); //toutes les touches pour les mouvements du Runner

            if(events.key.keysym.sym == SDLK_r) //temporaire c'est pour tp le runner sil tombe
            {
                Runner.setAbsPosX(0);
                Runner.setAbsPosY(0);
                Runner.refreshHitbox();
                Runner.setIsTouchingGround(false);
                Runner.setIsJumping(false);
            }
            break;

            case SDL_KEYUP: //a la fin de l'appui d'une touche
                
            keysUpForRunnerMovements(SDLK_LEFT, SDLK_RIGHT); //toutes les touches pour les mouvements du Runner
                
            break;

            //evenement souris
            case SDL_MOUSEMOTION:

            canonRotationWithMouse();

            break;

            case SDL_MOUSEBUTTONDOWN:
            
            Canon.Weapon.shoot();

            break;
        }
    
    return true;
}

void game::refreshGame()
{
    canonRotationAnimation();
    refreshProjectileState();
    Canon.Weapon.refreshProjectilesMovements();

    staticRunnerAnimation();
    runningRunnerAnimation();
    Runner.refreshMovement();   //on actualise l'etat du deplacement
    Runner.refreshJump();   //on actualise l'etat du saut
    Runner.gravity(Map.arrPlateforms); //on actualise les variables liées a la gravite

    
}


bool game::menuLoop()
{
        switch (events.type)    //test de l'evenement entendu
        {
            case SDL_WINDOWEVENT:   //fermeture fenetre
            if(events.window.event == SDL_WINDOWEVENT_CLOSE)
                return false;
            break;

            case SDL_KEYDOWN:   //a l'appui d'une touche

            if (events.key.keysym.sym == SDLK_ESCAPE) //fermeture de la fenêtre si on appui sur échap
            {
                return false;
            }
            break;

            case SDL_MOUSEBUTTONDOWN: // evenement de clic de souris
            if(events.button.button == SDL_BUTTON_LEFT) // evenement du clic sur le cote gauche de la souris
            {
                unsigned int clicx = events.button.x; // coordonnée x du clic
                unsigned int clicy = events.button.y; // coordonnée y du clic
                if( ( clicx > Button.getposXJouer() ) && ( clicx < Button.getposXJouer() + SquareSizeButton ) && ( clicy > Button.getposYJouer() ) && ( clicy < Button.getposYJouer()+ SquareSizeButton ))
                //si les coordonnées du clic sont comprises dans le bouton, alors on affiche 1, sinon on affiche 0,
                {
                    dansLeMenu = false;
                }
                else if(( clicx > Button.getposXQuit() ) && ( clicx < Button.getposXQuit() + SquareSizeButton ) && ( clicy > Button.getposYQuit() ) && ( clicy < Button.getposYQuit()+ SquareSizeButton ))
                {
                    return false;
                } 
            } 
            break; 
        }
        
    return true;
}


int game::testWinner()   //-1 canon win, 0 no win, 1 runner win
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect winRect = {0, 0, w, h};


    if(Runner.getLife() == 0 || !SDL_HasIntersection(&winRect, &Runner.getHitboxRect()))   //si le runner est mort, canon gagne
    {
        return -1;
    }
    
    if(Runner.getNbItem() == 5)  //si le runner a toutes les pieces, runner gagne
    {
        return 1;
    }

    return 0;
}


bool game::playLoop()
{
    bool windowsRunning = true;
    int winState = 0;
    int roundNb = 0;

    if(dansLeMenu)
    {
        while(SDL_PollEvent(&events))
        {
            windowsRunning = menuLoop();
        }

        displayMenu();

        if(!windowsRunning)
        {
            return false;
        }

        return true;
    }


    else
    {
        while(roundNb < 4)
        {
            resetRound(roundNb%3);
            displayAll();

            while(winState == 0)    //un round continu tant qu'il n'y a pas de gagnant
            {
                while (SDL_PollEvent(&events))  //tant qu'on "entend" des evenements
                {
                    windowsRunning = eventLoop();
                }

                refreshGame();
                winState = testWinner();

                displayAll();

                if(!windowsRunning)
                {
                    return false;
                }

            }
            NbCoinsCollected = 0;
            

            switch (winState)
            {
            case -1:
                scoreCanon++;
                winState = 0;
                

                SDL_RenderCopy(renderer, textureCanonWinScreen, NULL, NULL);
                SDL_RenderPresent(renderer);

                SDL_Delay(500);

                break;
            
            case 1:
                scoreRunner++;
                winState = 0;

                SDL_RenderCopy(renderer, textureRunnerWinScreen, NULL, NULL);
                SDL_RenderPresent(renderer);

                SDL_Delay(500);

                break;
            }

            roundNb++;
            refreshGame();
            Runner.refreshHitbox();
            displayAll();
        }

        if (scoreCanon > scoreRunner)  //si le canon a gagné
        {           
            SDL_RenderCopy(renderer, textureCanonWinTheGame, NULL, NULL);
        }
        else if (scoreCanon < scoreRunner) //si le runner a gagné
        {
            SDL_RenderCopy(renderer, textureRunnerWinTheGame, NULL, NULL);
        }
        else    //s'il y a égalité
        {
            SDL_RenderCopy(renderer, textureItsADrawScreen, NULL, NULL);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);

        scoreCanon = 0;
        scoreRunner = 0;

        dansLeMenu = true;
    }


}

void game::resetRound(int roundNb)
{
    createMapElement(mapList[roundNb]);

    Runner.reset(Map.runnerSpawnPoint.x, Map.runnerSpawnPoint.y);
    Canon.reset(Map.canonSpawnPoint.x, Map.canonSpawnPoint.y);
    Runner.refreshHitbox();
    Canon.refreshPosition();
}

//---------------------------------FONCTIONS D'AFFICHAGE-------------------------------------------------

void game::drawLinesRunner() /// dessine les lignes autour du personnage (hitbox)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); /// configure la couleur que l'on prend pour dessiner en tant que vert
    SDL_RenderDrawRect(renderer, &Runner.getHitboxRect());
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &Runner.getHitboxRelRect());
}

void game::drawRectPlateforms()    /// fonction dessiner un rectangle, prend en paramètre un pointeur sur tableau de rectangles, dans le but d'appeler le tableau de rectangles de la classe map
{    
   for(int i = 0; i< Map.arrPlateforms.size(); i++)
   {
       SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /// définit la couleur
       SDL_RenderFillRect(renderer, &Map.arrPlateforms[i]); /// dessines un rectangle des coordonnées de tab[i], tab contient des coordonnées de rectangles différentes pour chaque i

   }
}

void game::drawRectWalls(SDL_Rect* tab)
{
    for(int i = 0; i < 2; i++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &tab[i]);
    }
}

void game::drawCanon()
{
    SDL_RenderCopy(renderer, textureWeapon, &Canon.Weapon.srcRectsprite[Canon.Weapon.getSelectedSpriteFrame()], &Canon.getWeaponDestSpriteRect());

    SDL_RenderCopy(renderer, textureCanon, NULL, &Canon.getHitboxRect());  
}

void game::drawProjectiles()
{
    for(int i = 0; i < int(Canon.Weapon.arrBullet.size()); i++)
    {
        SDL_RenderCopy(renderer, textureBullet, NULL , &Canon.Weapon.arrBullet[i].getHitbox());
    }
}


void game::drawMap()
{
    SDL_RenderCopy(renderer, textureBackground, NULL, NULL);
    drawRectPlateforms();
    drawCoinsMap();
    if(Heart.getshowHeart()){
        SDL_RenderCopy(renderer, textureHeartMap, NULL, &Heart.getHitboxRectHeart());
    }
}

void game::drawMenu() // fonction qui dessine le bouton (class button) sur une fenêtre noire
{
    SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureMenu, NULL, NULL);

   // Button.setHitboxRectJouer(PosXButtonJouer, PosYButtonJouer); // On actualise la hitbox du bouton pour qu'il ait les bonnes coordonnées

    SDL_RenderCopy(renderer, textureMenu, NULL, NULL);
    SDL_RenderCopy(renderer, textureButtonJouer, &Button.getHitboxRectInit(), &Button.getHitboxRectJouer());
    SDL_RenderCopy(renderer, textureButtonQuit, &Button.getHitboxRectInit(), &Button.getHitboxRectQuit());
}

void game::drawHud()
{
    drawCoinsHud();
    drawHeartHud();
}

void game::drawCoinsMap() // fonction qui affichent les pièces de la map en fonction d'un
                                // tableau de type pièce
{
    for(unsigned int i=0; i<Map.getSizeListCoinMap(); i++)
    {
        if(Map.listCoinMap[i].getCoinOnMap())
        {
        Map.listCoinMap[i].refreshHitboxCoin(); //nouvelle fonction rajouter dans coin, en gros c'est ça qui buguait
        //comme hitbox est défini au début et qu'on définit des val x et y, elle gardait celle-ci

        SDL_RenderCopy(renderer, textureCoinMap, &Coin.getCurrentSpriteCoinFrame(), &Map.listCoinMap[i].getHitboxRectCoin());
        //ici on copie dans le rendu la même texture pour toutes les pièces et le me sprite actuel pour toutes
        //les pièces, comme ça elles sont synchros. On les met dans la hitbox qui correspond à chaque coordonée
        //du tableau de pièces.
        }  
    }
}

void game::drawCoinsHud()
{
    for(unsigned int i=0; i<NbCoinsCollected; i++)
    {
        Hud.listCoinScore[4 - i].refreshHitboxCoin();
        SDL_RenderCopy(renderer, textureCoinHud, &Coin.srcRectSpriteCoin[0], &Hud.listCoinScore[4 - i].getHitboxRectCoin());
    }
}

void game::drawHeartHud()
{
    if(Runner.getLife() == 0)
    {
        //Victoire Canon
    }
    else
    for(unsigned int i=0; i<Runner.getLife(); i++)
    {
        Hud.listHeart[i].refreshHitboxHeart();
        SDL_RenderCopy(renderer, textureHeartHud, NULL, &Hud.listHeart[i].getHitboxRectHeart());
    }
}

void game::InteractRunnerCoins() // si il y a interaction entre le runner et une pièce 
// du tableau, alors le booléen correspondant à cette pièce devient faux. Alors,
//dans drawCoins, le "if" n'est plus validé et elle ne s'affiche plus. Cependant, la hitbox ne disparaît
//pas, il continue donc d'y avoir des interactions. Donc compliqué et inutile de compter le nb d'items
// via cette fonction.
{
    for(unsigned int i=0; i < Map.getSizeListCoinMap(); i++)
    {
        if(SDL_HasIntersection(&Runner.getHitboxRect(),&Map.listCoinMap[i].getHitboxRectCoin()) && Map.listCoinMap[i].getCoinOnMap())
        {
            Map.listCoinMap[i].setCoinOnMap(false);
            Hud.listCoinScore[i].setIsCollected(true); //On dit que le coin correspondant est collecté
        }
    }
}

void game::InteractRunnerHeart()
{
    if(SDL_HasIntersection(&Runner.getHitboxRect(),&Heart.getHitboxRectHeart()) && Heart.getshowHeart())
    {
        Heart.setIsCollected(true);
        Heart.setshowHeart(false);
    }
}

void game::CountItemsCollected()
{
    NbCoinsCollected = 0;

    for(unsigned int i=0; i<Hud.getSizelistCoin(); i++)
    {
        if(Hud.listCoinScore[i].getIsCollected())
        {
            NbCoinsCollected = NbCoinsCollected + 1;
            Runner.setNbItem(NbCoinsCollected);
        }
    }
}

void game::EventsLife()
{
    if(Heart.getIsCollected())
    {
        Runner.gainALife();
        Heart.setIsCollected(false);
    }
}

void game::displayMenu()
{
    drawMenu();
    SDL_RenderPresent(renderer);
}


void game::displayMap()
{   
    /// initialise le rendu à la couleur rouge
    /*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /// colores le fond de la fenêtre en rouge
    SDL_RenderClear(renderer);  ///initialise le rendu à la couleur verte*/
    CountItemsCollected();
    EventsLife();
    drawMap();
    drawHud();
    InteractRunnerCoins();
    InteractRunnerHeart();

    //drawLinesRunner(); // appel à la fonction drawLines qui dessine les lignes atour du personnage
    
    SDL_RenderCopy(renderer, textureRunner, &Runner.getCurrentSpriteFrame(), &Runner.getHitboxRect());  //on copie le sprite du personnage au nouvel emplacement de la hitbox faire bien gaffe a ne pas mettre la hitbox en tant que rect_src
    
    drawProjectiles();
    drawCanon();

    //SDL_RenderCopy(renderer, textureButton, &Button.getHitboxRectInit(), &Button.getHitboxRect());
    
    
    SDL_RenderCopy(renderer, textureCanon, &Canon.getHitboxRectInit(), &Canon.getHitboxRect());
   // SDL_RenderCopy(renderer, textureWritingLives, NULL, &RectWritingZone);


    SDL_RenderPresent(renderer);    // actualise le rendu /!\ IMPORTANT : actualiser le rendu une seule fois seulement (lorsqu'on a tout "dessiné")
}

void game::displayAll()
{
    if(dansLeMenu)
    {
        displayMenu();
    }
    else
    {
        displayMap();
    }
}

//---------------------ANIMATIONS----------------

void game::staticRunnerAnimation()
{    
    if(TimerRunner.timePassed() > 500 && !Runner.getIsMoving())    //toutes les 0.5s on change de sprite (quand le Runner ne bouge pas)
    {
        switch (Runner.getSelectedSpriteFrame()) //permet de permuter entre sprite 1 et 2 ou sprite 2 et 3 (animation respiration a l'arret )
        {
            case 0: //l'equivalent du OR dans un switch (fallthrough)
            case 8:
                Runner.setSelectedSpriteFrame(Runner.getSelectedSpriteFrame() + 1);
                Runner.setCurrentSpriteFrame(Runner.srcRectSprite[Runner.getSelectedSpriteFrame()]);   //sprite suivant
                TimerRunner.start();
            break;

            case 1:
            case 9:
                Runner.setSelectedSpriteFrame(Runner.getSelectedSpriteFrame() - 1);
                Runner.setCurrentSpriteFrame(Runner.srcRectSprite[Runner.getSelectedSpriteFrame()]);  //sprite precedent
                TimerRunner.start();
            break;
                    
            default:
            break;
        } 
    }
}

void game::runningRunnerAnimation()
{
    if (TimerRunner.timePassed() > 100 && Runner.getIsMoving()) //toutes les 0.1s quand le joueur est en mouvement
    {
        if ((Runner.getSelectedSpriteFrame() >= 2 && Runner.getSelectedSpriteFrame() < 7) || (Runner.getSelectedSpriteFrame() >= 10 && Runner.getSelectedSpriteFrame() < 15))   //si le sprite selectionné n'est pas le dernier de l'animation
        {
            Runner.setSelectedSpriteFrame(Runner.getSelectedSpriteFrame() + 1);
            Runner.setCurrentSpriteFrame(Runner.srcRectSprite[Runner.getSelectedSpriteFrame()]);  //on passe au sprite suivant

            TimerRunner.start();
        }

        else if (Runner.getSelectedSpriteFrame() == 7 || Runner.getSelectedSpriteFrame() == 15)   //si le sprite selectionné est le dernier de l'animation
        {
            Runner.setSelectedSpriteFrame(Runner.getSelectedSpriteFrame() - 5);
            Runner.setCurrentSpriteFrame(Runner.srcRectSprite[Runner.getSelectedSpriteFrame()]); //on revient au premier sprite de l'animation
            TimerRunner.start();
        }
    }
    
}

void game::canonRotationAnimation()
{
    Canon.Weapon.setSelectedSpriteFrame(int(Canon.getAngle()/(2*PI/16)));
    
}
void game::staticCoinAnimation()
{    
    if(TimerCoin.timePassed() > 300)    //toutes les 0.1s on change de sprite (la pièce fait donc un tour en 0,4s)
    {
        switch (Coin.getSelectedSpriteCoinFrame()) //permet de permuter entre sprite 1, 2, 3 et 4, puis de retourner au sprite 1
        {
            case 0:
            case 1:
            case 2:
                Coin.setSelectedSpriteCoinFrame(Coin.getSelectedSpriteCoinFrame() + 1);
                Coin.setCurrentSpriteCoinFrame(Coin.srcRectSpriteCoin[Coin.getSelectedSpriteCoinFrame()]);
                TimerCoin.start();
            break;

            case 3:
                Coin.setSelectedSpriteCoinFrame(0);
                Coin.setCurrentSpriteCoinFrame(Coin.srcRectSpriteCoin[Coin.getSelectedSpriteCoinFrame()]);  //sprite suivant
                TimerCoin.start();
            break;

            default:
            break;
        } 
    }
}