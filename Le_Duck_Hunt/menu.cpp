#include "main.h"

void menu(SDL_Surface *ecran, Sprites &sprites, Boutons &boutons, int &modeMenu, int &modeJeu, SourisEvent &sourisEvent, Time &time, Message msgs[], Partie &partie, Chien &chien)
{
    bool sortir = false;
    bool clicGaucheTemp;
    while (!sortir && modeMenu!=0)
    {
        clicGaucheTemp = false;
        if (getEvents(sourisEvent, 1))
        {
            modeMenu = 0;
            modeJeu = 0;
        }
        if (sourisEvent.clicGauche)
        {
            clicGaucheTemp = true;
        }
        time.currentTime = SDL_GetTicks();
        sourisEvent.clicGauche = clicGaucheTemp;
        switch (modeMenu)
        {
        case 0:
            sortir = true;
            break;
        case 1 :
            boutons.bouton[BOUTON_PLAY].position.x = (LARGEUR/2)-(boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_PLAY].position.y = 200;

            boutons.bouton[BOUTON_QUIT].position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_QUIT].position.y = 400;
            if (time.currentTime >= time.timeFps + time.fpsTime)
            {
                showMenu(ecran, sprites, boutons, modeMenu, msgs, sourisEvent.sx, sourisEvent.sy);
                time.timeFps = time.currentTime;
            }

            if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_QUIT], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 0;
                modeJeu = 0;

            }
            else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_PLAY], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeJeu = 1;
                modeMenu = 0;
                initChien(chien);

                sprites.canardActifs = 2;

                for (int i = 0 ; i < sprites.canardActifs ; i++)
                {
                    sprites.canard[i].type = alea(1, 3);
                    initCanard(sprites.canard[i]);
                }
                initPartie(partie, sprites.canardActifs);
                initTableau(partie.tableauChasse, sprites);
            }
            break;
        case 5 :
            boutons.bouton[BOUTON_REPRENDRE].position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_REPRENDRE].position.y = 200;

            boutons.bouton[BOUTON_QUIT].position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_QUIT].position.y = 400;

            if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_QUIT], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 1;
            }
            else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_REPRENDRE], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 0;
            }

            if (time.currentTime >= time.timeFps + time.fpsTime)
            {
                showMenu(ecran, sprites, boutons, modeMenu, msgs, sourisEvent.sx, sourisEvent.sy);
                time.timeFps = time.currentTime;
            }
            break;
        case 6:

            break;
        default:
            break;
        }
        SDL_Flip(ecran);
    }
}

bool testHoverBouton(int sx, int sy, Bouton sprite, SDL_Rect lecture)
{
    return((sx < sprite.position.x+lecture.w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+lecture.h));
}
