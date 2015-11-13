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
    bool continuer = true;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("DuckHunt", NULL);

    ecran = SDL_SetVideoMode(SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, BPP, SDL_HWSURFACE | SDL_FULLSCREEN);

   // Uint8 *keystates = SDL_GetKeyState(NULL);

    Bouton bouton;

    while(continuer)
    {
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
        }
        afficherImage(ecran);
    }

    SDL_FreeSurface(ecran);

    SDL_Quit();

    return EXIT_SUCCESS;
}
// test

