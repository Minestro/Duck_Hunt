#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#define BPP 32

#include "images.h"
#include "collerSurface.h"


using namespace std;

int main()
{
    SDL_Surface *ecran;
    SDL_Event evenements;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    const int HAUTEUR = SDL_GetVideoInfo()->current_h;
    const int LARGEUR = SDL_GetVideoInfo()->current_w;

    SDL_WM_SetCaption("DuckHunt", NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE | SDL_FULLSCREEN);

    Uint32 noir = SDL_MapRGB(ecran->format, 0, 0, 0);

    Uint8 *keystates = SDL_GetKeyState(NULL);

    Images images;
    charger(images);
    placer(images);

    do
    {
        SDL_PollEvent(&evenements);

        SDL_FillRect(ecran, NULL, noir);
        collerSurface(images.backGame, ecran, NULL);
        collerSurface(images.backGameBlit, ecran, NULL);

        SDL_Flip(ecran);

    } while(!keystates[SDLK_q]);

    libererImages(images);
    SDL_FreeSurface(ecran);

    SDL_Quit();

    return EXIT_SUCCESS;
}

