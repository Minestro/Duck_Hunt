#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

    Uint32 noir = SDL_MapRGB(ecran->format, 0, 0, 0);

    Uint8 *keystates = SDL_GetKeyState(NULL);

    SDL_Rect image;


    while(continuer)
    {
        SDL_FillRect(ecran, NULL, noir);

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

