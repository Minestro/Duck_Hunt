#include "main.h"

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SourisEvent sourisEvent;
    Uint8 *keystates = SDL_GetKeyState(NULL);

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_WM_SetCaption("DuckHunt", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("sprites/icon.bmp"), NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE);


    int fpsTime = (1/(FPS_MAX*1.0)*1000);    //Calcule en ms le temps entre chaque actualisation d'image à partir de la constante FPS_LIMIT.
    Uint32 currentTime, cycleRefresh, cycleEvents;
    currentTime = cycleRefresh = cycleEvents = 0;

    int modeJeu = 0;    //Le mode de jeu.
    int modeMenu = 1;   //Détermine la page du menu à afficher.

    Boutons boutons;
    Sprites sprites;
    Police police;
    chargerImages(sprites, boutons);
    initBouton(boutons.quit, 0);
    initBouton(boutons.play, 1);

    menu(sprites, boutons, modeMenu, modeJeu, ecran, police, keystates, sourisEvent);
    while ((modeJeu!=0)&&!(getEvents(sourisEvent, keystates)))
    {
        currentTime = SDL_GetTicks();
        menu(sprites, boutons, modeMenu, modeJeu, ecran, police, keystates, sourisEvent);
        if (currentTime>=cycleRefresh+fpsTime)
        {
            genererRendu(ecran, sprites, sourisEvent);
            cycleRefresh = currentTime;
        }
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}

