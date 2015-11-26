#include "main.h"

int main()
{
    /* INITIALISATIONS DES BIBLIOTHEQUES : IMG, SDL */
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_Init(SDL_INIT_VIDEO);

    /* Création de la surface d'écran */
    SDL_Surface *ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE);

    /* Titre */
    SDL_WM_SetCaption("Duck Hunt", NULL);

    /* Icone */
    SDL_WM_SetIcon(SDL_LoadBMP("sprites/icon.bmp"), NULL);

    /* Initialisation des variables en rapport avec le temps */
    Time temps;
    initTime(temps);
    srand(time(NULL));

    int modeJeu = 0;    // Le mode de jeu.
    int modeMenu = 1;   // Détermine la page du menu à afficher.
    int shots = 3;

    Boutons boutons;
    Sprites sprites;

    chargerImages(sprites, boutons);
    sprites.canardActifs = 2;

    for (int i=0; i<sprites.canardActifs; i++)
    {
        sprites.canard[i].type = 0;
        initCanard(sprites.canard[i]);
    }
    initBouton(boutons.quit, 0);
    initBouton(boutons.play, 1);
    Uint8 *keystate = SDL_GetKeyState(NULL);

    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);
    SDL_ShowCursor(SDL_DISABLE);

    do
    {
        temps.currentTime = SDL_GetTicks();
        menu(sprites, boutons, modeMenu, modeJeu, ecran, sourisEvent, temps);

        for (int i=0; i<sprites.canardActifs; i++)
        {
            if ((temps.currentTime >= sprites.canard[i].vitesseTime + sprites.canard[i].vitesse)&&(sprites.canard[i].etat > 0))
            {
                shot(sourisEvent, sprites.canard[i], shots, i, sprites.canardActifs);
                mouvementsCanard(sprites.canard[i]);
                changementDirection(sprites.canard[i]);
                controleCanard(sprites.canard[i]);

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
        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }
        SDL_Delay(1);

    } while (modeJeu != 0);
    SDL_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

