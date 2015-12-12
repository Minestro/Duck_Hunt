#include "main.h"

void menu(SDL_Surface *ecran, Sprites &sprites, Boutons boutons, int &modeMenu, int &modeJeu, SourisEvent &sourisEvent, Time &time, Message msgs[], Partie &partie, Chien &chien)
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
        if (true)//((time.currentTime >= time.timeMenu + time.menuTime) || modeMenu==0)
        {
            sourisEvent.clicGauche = clicGaucheTemp;
            switch (modeMenu)
            {
            case 0:
                sortir = true;
                break;
            case 1 :
                boutons.play.position.x = (LARGEUR/2)-(boutons.lecture[0].w/2);
                boutons.play.position.y = 200;

                boutons.quit.position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
                boutons.quit.position.y = 400;
                showMenu(ecran, sprites, boutons, modeMenu, msgs, sourisEvent.sx, sourisEvent.sy);

                if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.quit, boutons.lecture[0]))&&sourisEvent.clicGauche)
                {
                    modeMenu = 0;
                    modeJeu = 0;

                }
                else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.play, boutons.lecture[0]))&&sourisEvent.clicGauche)
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
                }
                break;
            case 5 :
                boutons.reprendre.position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
                boutons.reprendre.position.y = 200;

                boutons.quit.position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
                boutons.quit.position.y = 400;

                if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.quit, boutons.lecture[0]))&&sourisEvent.clicGauche)
                {
                    modeMenu = 1;
                }
                else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.reprendre, boutons.lecture[0]))&&sourisEvent.clicGauche)
                {
                    modeMenu = 0;
                }

                showMenu(ecran, sprites, boutons, modeMenu, msgs, sourisEvent.sx, sourisEvent.sy);
                break;
            default:
                break;
            }
            time.timeMenu = time.currentTime;
        }
        SDL_Flip(ecran);
    }
}

bool testHoverBouton(int sx, int sy, Bouton sprite, SDL_Rect lecture)
{
    return((sx < sprite.position.x+lecture.w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+lecture.h));
}
