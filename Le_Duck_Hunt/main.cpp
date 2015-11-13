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
    int modeJeu = 0;    //Le mode de jeu.
    int modeMenu = 0;   //Détermine la page du menu à afficher.

    // Uint8 *keystates = SDL_GetKeyState(NULL);

    Boutons bouton;
    Sprites sprites;
    chargerImages(sprites, bouton);

    Police police;

    menu(sprites.background_menu, bouton, modeMenu, modeJeu, ecran, police);
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
        menu(sprites.background_menu, bouton, modeMenu, modeJeu, ecran, police);
        afficherImage(ecran, sprites);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}

