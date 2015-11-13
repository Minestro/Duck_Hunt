#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "main.h"
#define BPP 32

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SDL_Event evenements;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_WM_SetCaption("DuckHunt", NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE | SDL_FULLSCREEN);

    bool continuer = true;
    // Uint8 *keystates = SDL_GetKeyState(NULL);

    Bouton bouton;

    Uint8 *keystates = SDL_GetKeyState(NULL);

    //charger(images);
    //placer(images);

    while(SDL_PollEvent(&evenements))
    {
        switch(evenements.type)
        {
        case SDL_QUIT:
            continuer = false;
            break;
        default:
            break;
        }
        afficherImage(ecran);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}

