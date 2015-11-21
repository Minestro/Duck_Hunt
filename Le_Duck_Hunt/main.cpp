#include "main.h"

using namespace std;

int main()
{
    SDL_Surface *ecran;
    SourisEvent sourisEvent;
    initSourisEvent(sourisEvent);

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
    sprites.canard.type = 0;
    initCanard(sprites.canard);
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
        if (time.currentTime >= sprites.canard.vitesseTime + sprites.canard.vitesse)
        {
            mouvementsCanard(sprites.canard);
            std::cout << sprites.canard.image.position.x << std::endl;
            sprites.canard.vitesseTime = time.currentTime;
        }
        if ((time.currentTime >= sprites.canard.vitesseAnimationTime + sprites.canard.vitesseAnimation)&&(sprites.canard.vecteurPositionY<0))
        {
            switchSprite(sprites.canard.image, sprites.canard.nbFrames, sprites.canard.pxParFrame, sprites.canard.cycleSprite);
            sprites.canard.vitesseAnimationTime = time.currentTime;
        }
        if (time.currentTime>=time.timeFps+time.fpsTime)
        {
            genererRendu(ecran, sprites, sourisEvent);
            changementDirection(sprites.canard);
            time.timeFps = time.currentTime;
        }
        SDL_Delay(1);
    }
    SDL_Quit();
    //vider les images
    return EXIT_SUCCESS;
}

