#include "file.h"
#include "getEvents.h"
#include "images.h"
#include "init.h"
#include "menu.h"
#include "mouvements.h"
#include "relancerPartie.h"
#include "shot.h"
#include "show.h"
#include "switchSprite.h"


int main(int argc, char* argv[])
{
    /* INITIALISATIONS DES BIBLIOTHEQUES : IMG, SDL, TTF */
    IMG_Init(IMG_INIT_PNG);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Message msgs[NOMBRE_MESSAGES];
    initMessage(msgs);

    SDL_Surface *ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

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
    partie.score = 0;
    partie.niveau = 0;
    Sprites sprites;
    Chien chien;

    Boutons boutons;
    initBouton(boutons);

    chargerImages(sprites, chien, boutons, "classique");
    boutons.bouton[BOUTON_THEME_CLASSIQUE].actif = true;

    Uint8 *keystate = SDL_GetKeyState(NULL);
    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);

    initFichiers();

    SDL_ShowCursor(SDL_DISABLE);

    menu(ecran, sprites, boutons, modeMenu, modeJeu, sourisEvent, temps, msgs, partie, chien);
    while (modeJeu != 0)
    {
        if (modeMenu != 0)
        {
            menu(ecran, sprites, boutons, modeMenu, modeJeu, sourisEvent, temps, msgs, partie, chien);
        }
        temps.currentTime = SDL_GetTicks();
        partie.alreadyShot = partie.alreadyGetEvent = partie.alreadyClic = false;
        for (int i = 0 ; i < sprites.canardActifs ; i++)
        {
            shoot(sourisEvent, sprites.canard[i], partie, temps, modeJeu);
            if ((temps.currentTime >= sprites.canard[i].vitesseTime + sprites.canard[i].vitesse))
            {
                mouvementsCanard(sprites.canard[i]);
                detectionBordsCanard(sprites.canard[i], partie, i);
                changementDirection(sprites.canard[i]);
                if(sprites.canard[i].etat == TOUCHED)
                {
                    touched(sprites.canard[i], temps);
                }
                sprites.canard[i].vitesseTime = temps.currentTime;
            }
            if (temps.currentTime >= sprites.canard[i].vitesseAnimationTime + sprites.canard[i].vitesseAnimation)
            {
                switchSpriteCanard(sprites.canard[i]);
                sprites.canard[i].vitesseAnimationTime = temps.currentTime;
            }
        }
        if(partie.shots <= 0)
        {
            for(int i = 0 ; i < sprites.canardActifs ; i++)
            {
                canardSurvivant(sprites, partie, i);
            }
        }
        if (temps.currentTime >= chien.vitesseAnimationTime + chien.vitesseAnimation)
        {
            switchSpriteChien(chien, partie);
            controlesChien(chien, partie, sprites);
            ramasserCanard(chien, partie, sprites);

            chien.vitesseAnimationTime = temps.currentTime;
            ramasserCanard(chien, partie, sprites);
        }
        if(partie.relancer)
        {
            relancerPartie(partie, sprites);
        }
        if(partie.round >= 5)
        {
            if(finPartie(partie))
            {
                if (testHighScore("scoresClassic", partie))
                {
                    modeMenu = 8;
                }
                else
                {
                    modeMenu = 9;
                }
            }
            else
            {
                partie.round = 0;
                partie.niveau ++;
                initPartie(partie, sprites.canardActifs);
                partie.jeu = true;
                for (int i=0; i<sprites.canardActifs; i++)
                {
                    initCanard(sprites.canard[i], partie);
                }
                initTableau(partie.tableauChasse, sprites);
                modeMenu = 6;
            }
        }
        if (keystate[SDLK_ESCAPE])
        {
            modeMenu = 5;
        }
        if (temps.currentTime >= temps.timeFps + temps.fpsTime)
        {
            genererRendu(ecran, sprites, sourisEvent, partie, chien, msgs);
            SDL_Flip(ecran);
            temps.timeFps = temps.currentTime;
        }

        SDL_Delay(1);
    }
    libererImages(sprites, chien, boutons);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    return EXIT_SUCCESS;
}

