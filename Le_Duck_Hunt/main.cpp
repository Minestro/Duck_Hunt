#include "main.h"

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_WM_SetCaption("Duck Hunt", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("sprites/icon.bmp"), NULL);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE);

    Time time;
    initTime(time);

    int modeJeu = 0;    //Le mode de jeu.
    int modeMenu = 1;   //Détermine la page du menu à afficher.

    Boutons boutons;
    Sprites sprites;
    chargerImages(sprites, boutons);
    sprites.canardActifs = 10;
    //sprites.canard[0].type = 0;
    //sprites.canard[1].type = 0;
    for (int i=0; i<sprites.canardActifs; i++)
    {
        sprites.canard[i].type = 0;
        initCanard(sprites.canard[i]);

    }
    initBouton(boutons.quit, 0);
    initBouton(boutons.play, 1);

    menu(sprites, boutons, modeMenu, modeJeu, ecran, sourisEvent, time);
    while (modeJeu!=0)
    {
        Uint8 *keystate = SDL_GetKeyState(NULL);
        time.currentTime = SDL_GetTicks();
        menu(sprites, boutons, modeMenu, modeJeu, ecran, sourisEvent, time);
        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }
        for (int i=0; i<sprites.canardActifs; i++)
        {
            if (time.currentTime >= sprites.canard[i].vitesseTime + sprites.canard[i].vitesse)
            {
                mouvementsCanard(sprites.canard[i]);
                changementDirection(sprites.canard[i]);
                sprites.canard[i].vitesseTime = time.currentTime;
            }
            if (time.currentTime >= sprites.canard[i].vitesseAnimationTime + sprites.canard[i].vitesseAnimation)
            {
                switchSprite(sprites.canard[i].image, sprites.canard[i].nbFrames, sprites.canard[i].pxParFrame, sprites.canard[i].cycleSprite);
                sprites.canard[i].vitesseAnimationTime = time.currentTime;
            }
        }
        if (time.currentTime>=time.timeFps+time.fpsTime)
        {
            genererRendu(ecran, sprites, sourisEvent);
            time.timeFps = time.currentTime;
        }
        SDL_Delay(1);
    }
    SDL_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

