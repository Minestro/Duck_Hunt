#include "main.h"

int main(int argc, char* argv[])
{
    /* INITIALISATIONS DES BIBLIOTHEQUES : IMG, SDL, TTF */
    IMG_Init(IMG_INIT_PNG);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Message msgScore;
    initMessage(msgScore);
    msgScore.position.x = 580;
    msgScore.position.y = 667;
    Message msgMenu;
    initMessage(msgMenu);
    msgMenu.fontSize = 45;
    msgScore.font = TTF_OpenFont("font/duck_hunt.ttf", msgScore.fontSize);
    msgMenu.font = TTF_OpenFont("font/duck_hunt.ttf", msgMenu.fontSize);

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
    Sprites sprites;

    chargerImages(sprites);

    Boutons boutons;
    initBouton(boutons);

    Chien chien;
    initChien(chien);

    sprites.canardActifs = 2;

    for (int i = 0; i<sprites.canardActifs; i++)
    {
        sprites.canard[i].type = alea(1, 2);
        initCanard(sprites.canard[i]);
    }

    initPartie(partie, sprites.canardActifs);

    Uint8 *keystate = SDL_GetKeyState(NULL);
    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);
    SDL_ShowCursor(SDL_DISABLE);


    do
    {
        menu(sprites, boutons, modeMenu, modeJeu, sourisEvent, temps, msgMenu);
        temps.currentTime = SDL_GetTicks();
        for (int i = 0 ; i < sprites.canardActifs ; i++)
        {
            getEvents(sourisEvent);
            if ((temps.currentTime >= sprites.canard[i].vitesseTime + sprites.canard[i].vitesse))
            {
                shoot(sourisEvent, sprites.canard[i], partie, i, sprites.canardActifs, temps);
                if(sprites.canard[i].etat == TOUCHED)
                {
                    touched(sprites.canard[i], temps, sprites.points);
                }
                mouvementsCanard(sprites.canard[i]);
                detectionBordsCanard(sprites.canard[i], partie);
                changementDirection(sprites.canard[i]);
                sprites.canard[i].vitesseTime = temps.currentTime;
            }
            if (temps.currentTime >= sprites.canard[i].vitesseAnimationTime + sprites.canard[i].vitesseAnimation)
            {
                switchSpriteCanard(sprites.canard[i]);
                sprites.canard[i].vitesseAnimationTime = temps.currentTime;
            }
        }
        if (temps.currentTime >= chien.vitesseAnimationTime + chien.vitesseAnimation)
        {
            switchSpriteChien(chien, partie);
            chien.vitesseAnimationTime = temps.currentTime;
        }

        if (temps.currentTime >= temps.timeFps + temps.fpsTime)
        {
            genererRendu(sprites, sourisEvent, partie, chien);
            showMessage(msgScore, intToString(partie.score));

            SDL_Flip(SDL_GetVideoSurface());

            temps.timeFps = temps.currentTime;
        }

        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }

        if(partieTerminee(partie))
        {
            relancerPartie(partie, sprites);
        }
        SDL_Delay(1);

    } while (modeJeu != 0);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

