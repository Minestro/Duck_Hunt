#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define BPP 32

#include "images.h"
#include "applySurface.h"

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SDL_Event evenements;
    bool continuer = true;

    SDL_Init(SDL_INIT_VIDEO);

    const int HAUTEUR = SDL_GetVideoInfo()->current_h;
    const int LARGEUR = SDL_GetVideoInfo()->current_w;

    SDL_WM_SetCaption("DuckHunt", NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE | SDL_FULLSCREEN);

    Uint32 noir = SDL_MapRGB(ecran->format, 0, 0, 0);

    Uint8 *keystates = SDL_GetKeyState(NULL);

    Images images;
    charger(images);


    while(continuer)
    {
        SDL_FillRect(ecran, NULL, noir);

        applySurface((LARGEUR - images.backGame.image->w) / 2, (HAUTEUR - images.backGame.image->w) / 2, images.backGame.image, ecran, NULL);

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
            if(keystates[SDLK_q])
            {
                continuer = false;
            }
        }

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(ecran);

    SDL_Quit();

    return EXIT_SUCCESS;
}

