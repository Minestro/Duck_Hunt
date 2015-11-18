#include "main.h"

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);
    Uint8 *keystate;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_WM_SetCaption("DuckHunt", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("sprites/icon.bmp"), NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE);

    Time time;
    initTime(time);

    int modeJeu = 0;    //Le mode de jeu.
    int modeMenu = 1;   //Détermine la page du menu à afficher.

    Boutons boutons;
    Sprites sprites;
    chargerImages(sprites, boutons);
    initCanard(sprites.canard);
    initBouton(boutons.quit, 0);
    initBouton(boutons.play, 1);

    menu(sprites, boutons, modeMenu, modeJeu, ecran, sourisEvent, time);
    while ((modeJeu!=0)&&!(getEvents(sourisEvent, time)))
    {
        Uint8 *keystate = SDL_GetKeyState(NULL);
        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }
        time.currentTime = SDL_GetTicks();
        menu(sprites, boutons, modeMenu, modeJeu, ecran, sourisEvent, time);
        if (time.currentTime%time.vitesseCanard==0)
        {
            mouvementsCanard(sprites.canard);
            switchSprite(sprites.canard);
        }
        if (time.currentTime%time.fpsTime==0)
        {
            genererRendu(ecran, sprites, sourisEvent);
            changementDirection(sprites.canard);
        }
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}

