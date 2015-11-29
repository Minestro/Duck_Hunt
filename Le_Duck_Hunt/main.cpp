#include "main.h"

int main(int argc, char* argv[])
{
    /* INITIALISATIONS DES BIBLIOTHEQUES : IMG, SDL */
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_Init(SDL_INIT_VIDEO);

    /* Création de la surface d'écran */

    SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE);
    // L'allocation de mémoire statique d'un SDL_Surface n'est pas utile, SDL le fait implicitement.
    // On appelera l'écran grâce au renvoie de SDL_GetVideoSurface().

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

    for (int i = 0; i<sprites.canardActifs; i++)
    {
        sprites.canard[i].type = alea(1, 3);
        initCanard(sprites.canard[i]);
    }
    initBouton(boutons.quit, 0);
    initBouton(boutons.play, 1);
    Uint8 *keystate = SDL_GetKeyState(NULL);


    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);
    SDL_ShowCursor(SDL_DISABLE);

  //  char niveau = 1;

    do
    {
        menu(sprites, boutons, modeMenu, modeJeu, sourisEvent, temps);
        temps.currentTime = SDL_GetTicks();


        for (int i = 0; i < sprites.canardActifs; i++)
        {
            if ((temps.currentTime >= sprites.canard[i].vitesseTime + sprites.canard[i].vitesse)&&(sprites.canard[i].etat > 0))
            {
                shoot(sourisEvent, sprites.canard[i], shots, i, sprites.canardActifs, temps);
                if(sprites.canard[i].etat == TOUCHED)
                {
                    touched(sprites.canard[i], temps);
                }
                mouvementsCanard(sprites.canard[i]);
                changementDirection(sprites.canard[i]);
                sprites.canard[i].vitesseTime = temps.currentTime;
            }
            if (temps.currentTime >= sprites.canard[i].vitesseAnimationTime + sprites.canard[i].vitesseAnimation)
            {
                switchSpriteCanard(sprites.canard[i]);
                sprites.canard[i].vitesseAnimationTime = temps.currentTime;
            }
        }

        if (temps.currentTime >= temps.timeFps + temps.fpsTime)
        {
            genererRendu(sprites, sourisEvent, shots);
            temps.timeFps = temps.currentTime;
        }
        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }

        SDL_Delay(10);

    } while (modeJeu != 0);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

