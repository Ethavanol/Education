#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL; // rendu -> ce qui s'affiche dans la fenetre
    bool quit = false;
    SDL_Event events;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Erreur : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    fenetre = SDL_CreateWindow("Flashing Boomer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, 0);
    rendu = SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);

    if(fenetre == NULL){
        SDL_Log("Erreur : Création de la fenêtre échouée > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(rendu == NULL){
        SDL_Log("Erreur : Création du rendu échoué > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(SDL_RenderClear(rendu) != 0){
        SDL_Log("Effacement rendu échoué > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_RenderPresent(rendu);

    while(!quit) {
        while( SDL_PollEvent( &events )) { /** si le joueur appuie sur la croix, la fenêtre se ferme */
            if (events.type == SDL_QUIT) quit = true;
            else if (events.type == SDL_KEYDOWN) {  
                switch (events.key.keysym.scancode)
                {   /** si le joueur appuie sur la touche exit/escape, la fenêtre se ferme */
                    case SDL_SCANCODE_ESCAPE:
                        quit = true;
                        break;

                    default: break;
                }
            }
        }
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return EXIT_SUCCESS;
}