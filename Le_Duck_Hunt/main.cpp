#include "main.h"

int main(int argc, char* argv[])
{
    /* INITIALISATIONS DES BIBLIOTHEQUES : IMG, SDL, TTF */
    IMG_Init(IMG_INIT_PNG);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // fonction chargerPolice dans init.cpp ?
    TTF_Font *police;
    police = TTF_OpenFont("font/duck_hunt.ttf", 80);

    /* Définition de l'écran */
    SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

    // L'allocation de mémoire statique d'un SDL_Surface n'est pas utile, SDL le fait implicitement avec SetVideoMode.
    // On appelera l'écran grâce au renvoie de sa fonction native GetVideoSurface().

    /* Titre */
    SDL_WM_SetCaption("Duck Hunt", NULL);

    /* Icone */
    SDL_WM_SetIcon(SDL_LoadBMP("sprites/icon.bmp"), NULL);

    /* Initialisation des variables en rapport avec le temps */
    Time temps;
    initTime(temps);
    srand((unsigned)time(NULL));

    int modeJeu = 0;    // Le mode de jeu.
    int modeMenu = 1;   // Détermine la page du menu à afficher.

    Partie partie;
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
    initPartie(partie, sprites.canardActifs);

    Uint8 *keystate = SDL_GetKeyState(NULL);
    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);
    SDL_ShowCursor(SDL_DISABLE);

    Message msgNiveau;
    /*msgNiveau.message = "Niveau";
    msgNiveau.couleurTexte = {0,0,0};
    msgNiveau.taille = 80;
    msgNiveau.tempsDAffichage = 3000;
    msgNiveau.position.x = 0;
    msgNiveau.position.y = 0;*/

    do
    {
        menu(sprites, boutons, modeMenu, modeJeu, sourisEvent, temps);
        temps.currentTime = SDL_GetTicks();
        for (int i = 0 ; i < sprites.canardActifs ; i++)
        {
            getEvents(sourisEvent);
            if ((temps.currentTime >= sprites.canard[i].vitesseTime + sprites.canard[i].vitesse))
            {
                shoot(sourisEvent, sprites.canard[i], partie, i, sprites.canardActifs, temps);
                if(sprites.canard[i].etat == TOUCHED)
                {
                    touched(sprites.canard[i], temps);
                }
                mouvementsCanard(sprites.canard[i]);
                detectionBords(sprites.canard[i], partie);
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
            showMessageScreen(police, msgNiveau);
            genererRendu(sprites, sourisEvent, partie);
            temps.timeFps = temps.currentTime;
        }
        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }


        // Je pense qu'il faut regrouper ces conditions dans une fonction relancerPartie(Partie &partie);
        // Beaucoup de simplification de code à faire à mon avis.

        if(partie.canardsEnVie == 0)
        {
            for (int i = 0; i < sprites.canardActifs; i++)
            {
                sprites.canard[i].type = alea(1, 3);
                initCanard(sprites.canard[i]);
            }
            partie.canardsEnVie = 2;
            partie.shots = 3;
            partie.round++;
        }

        if(partie.shots == 0)
        {
            partie.hit[partie.round * 2] = partie.hit[partie.round * 2 + 1] = HIT_FAILED;

            for (int i = 0; i<sprites.canardActifs; i++)
            {
                if(sprites.canard[i].etat != DEAD)
                {
                    SDL_FreeSurface(sprites.canard[i].image.source);
                }
            }
            partie.shots = 3;

            for (int i = 0; i<sprites.canardActifs; i++)
            {
                sprites.canard[i].type = alea(1, 3);
                initCanard(sprites.canard[i]);
            }
            partie.canardsEnVie = 2;
            partie.shots = 3;
            partie.round++;
        }


        SDL_Delay(1);

    } while (modeJeu != 0);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

