#include "main.h"

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SourisEvent sourisEvent;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_WM_SetCaption("DuckHunt", NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE);

    int modeJeu = 0;    //Le mode de jeu.
    int modeMenu = 1;   //Détermine la page du menu à afficher.

    Uint8 *keystates = SDL_GetKeyState(NULL);

    Boutons boutons;
    Sprites sprites;
    Police police;
    chargerImages(sprites, boutons);
    initBouton(boutons.quit, 0);
    initBouton(boutons.play, 1);

    menu(sprites, boutons, modeMenu, modeJeu, ecran, police, keystates, sourisEvent);
    while ((modeJeu!=0)&&!(getEvents(sourisEvent, keystates)))
    {
        menu(sprites, boutons, modeMenu, modeJeu, ecran, police, keystates, sourisEvent);
        int sx, sy;
        sx = sy = 100;
        genererRendu(ecran, sprites, sx, sy);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}

