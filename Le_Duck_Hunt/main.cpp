#include "main.h"

int main(int argc, char* argv[])
{
    /* INITIALISATIONS DES BIBLIOTHEQUES : IMG, SDL, TTF */
    IMG_Init(IMG_INIT_PNG);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Message msgs[5];
    initMessage(msgs);

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

    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        sprites.canard[i].type = alea(1, 3);
        initCanard(sprites.canard[i]);
    }

    initPartie(partie, sprites.canardActifs);

    Uint8 *keystate = SDL_GetKeyState(NULL);
    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);
    SDL_ShowCursor(SDL_DISABLE);
    do
    {
        menu(sprites, boutons, modeMenu, modeJeu, sourisEvent, temps, msgs);
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
                detectionBordsCanard(sprites.canard[i], partie, sprites.canardSprite);
                changementDirection(sprites.canard[i]);
                if(roundTerminee(partie, sprites.canard, sprites.canardActifs))
                {
          //          relancerPartie(partie, sprites);
                }
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
            msgs[MSG_SCORE].source = TTF_RenderText_Solid(msgs[MSG_SCORE].font, intToString(partie.score).c_str(), msgs[MSG_SCORE].textColor);
            SDL_BlitSurface(msgs[MSG_SCORE].source, NULL, SDL_GetVideoSurface(), &msgs[MSG_SCORE].position);
            SDL_FreeSurface(msgs[MSG_SCORE].source);
            SDL_Flip(SDL_GetVideoSurface());

            temps.timeFps = temps.currentTime;
        }

        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }
        SDL_Delay(1);

    }
    while (modeJeu != 0);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

