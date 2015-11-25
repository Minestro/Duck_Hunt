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

    Time temps;
    initTime(temps);
    srand(time(NULL));

    int modeJeu = 0;    //Le mode de jeu.
    int modeMenu = 1;   //Détermine la page du menu à afficher.
    int shots;

    Boutons boutons;
    Sprites sprites;
    chargerImages(sprites, boutons);
    sprites.canardActifs = 3;
    //sprites.canard[0].type = 0;
    //sprites.canard[1].type = 0;

    for (int i=0; i<sprites.canardActifs; i++)
    {
        sprites.canard[i].type = 0;
        initCanard(sprites.canard[i]);

    }
    initBouton(boutons.quit, 0);
    initBouton(boutons.play, 1);
    Uint8 *keystate = SDL_GetKeyState(NULL);

    menu(sprites, boutons, modeMenu, modeJeu, ecran, sourisEvent, temps);
    sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
    shots = 3;
    while (modeJeu!=0)
    {
        temps.currentTime = SDL_GetTicks();
        menu(sprites, boutons, modeMenu, modeJeu, ecran, sourisEvent, temps);
        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }
        for (int i=0; i<sprites.canardActifs; i++)
        {
            if ((temps.currentTime >= sprites.canard[i].vitesseTime + sprites.canard[i].vitesse)&&(sprites.canard[i].etat > 0))
            {
                shot(sourisEvent, sprites.canard[i], shots, i, sprites.canardActifs);
                mouvementsCanard(sprites.canard[i]);
                changementDirection(sprites.canard[i]);
                sprites.canard[i].vitesseTime = temps.currentTime;
            }
            if (temps.currentTime >= sprites.canard[i].vitesseAnimationTime + sprites.canard[i].vitesseAnimation)
            {
                switchSprite(sprites.canard[i].image, sprites.canard[i].nbFrames, sprites.canard[i].pxParFrame, sprites.canard[i].cycleSprite);
                sprites.canard[i].vitesseAnimationTime = temps.currentTime;
            }
        }
        if (temps.currentTime>=temps.timeFps+temps.fpsTime)
        {
            genererRendu(ecran, sprites, sourisEvent, shots);
            temps.timeFps = temps.currentTime;
        }
        SDL_Delay(1);
    }
    SDL_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

