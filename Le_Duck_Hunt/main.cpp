#include "main.h"

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SDL_Event evenements;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_WM_SetCaption("DuckHunt", NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE);

    int modeJeu = 0;    //Le mode de jeu.
    int modeMenu = 0;   //Détermine la page du menu à afficher.

    Uint8 *keystates = SDL_GetKeyState(NULL);

    Boutons boutons;
    Sprites sprites;
    Police police;
    chargerImages(sprites, boutons);
    initBouton(boutons.quit);

    menu(sprites, boutons, modeMenu, modeJeu, ecran, police, keystates);
    while (modeJeu!=0)
    {
        while(SDL_PollEvent(&evenements))
        {
            switch(evenements.type)
            {
            case SDL_QUIT:
                modeJeu = 0;
                break;
            default:
                break;
            }
        }
        menu(sprites, boutons, modeMenu, modeJeu, ecran, police, keystates);
        genererRendu(ecran, sprites);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}

