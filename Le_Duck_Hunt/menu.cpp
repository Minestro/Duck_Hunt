#include "main.h"

using namespace std;

void menu(Sprites sprites, Boutons boutons, int &modeMenu, int &modeJeu, SDL_Surface *ecran, SourisEvent &sourisEvent, Time &time)
{
    bool sortir = false;
    while (sortir == false)
    {
        sortir = getEvents(sourisEvent, time);
        switch (modeMenu)
        {
            case 0:
                sortir = true;
                break;
            case 1 :
                boutons.play.position.x=(LARGEUR/2)-(boutons.play.lecture[0].w/2);
                boutons.play.position.y=200;
                boutons.quit.position.x=(LARGEUR/2)-(boutons.quit.lecture[0].w/2);
                boutons.quit.position.y=400;
                showMenu(ecran, sprites, boutons, modeMenu, sourisEvent.sx, sourisEvent.sy);
                if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.quit))&&sourisEvent.bl)
                {
                    modeMenu = 0;

                } else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.play))&&sourisEvent.bl)
                {
                    modeJeu = 1;
                    modeMenu = 0;
                }
                SDL_Delay(10);
                break;
            case 5 :

                SDL_Delay(10);
                break;
            default:
                break;
        }
    }
}

bool testHoverBouton(int sx, int sy, Bouton sprite)
{
    return((sx < sprite.position.x+sprite.lecture[0].w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+sprite.lecture[0].h));
}
