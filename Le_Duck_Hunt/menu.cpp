#include "main.h"

void menu(Sprites sprites, Boutons boutons, int &modeMenu, int &modeJeu, SourisEvent &sourisEvent, Time &time, Message message)
{
    bool sortir = false;
    while (!sortir)
    {
        if (getEvents(sourisEvent))
        {
            sortir = true;
            modeJeu = 0;
        }
        time.currentTime = SDL_GetTicks();
        if ((time.currentTime >= time.timeMenu + time.menuTime) || (modeMenu == 0))
        {
            switch (modeMenu)
            {
                case 0:
                    sortir = true;
                    break;
                case 1 :
                    boutons.play.position.x = (LARGEUR/2)-(boutons.play.lecture[0].w/2);
                    boutons.play.position.y = 200;
                    boutons.quit.position.x = (LARGEUR/2)-(boutons.quit.lecture[0].w/2);
                    boutons.quit.position.y = 400;
                    showMenu(sprites, boutons, modeMenu, sourisEvent.sx, sourisEvent.sy);

                    if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.quit))&&sourisEvent.bl)
                    {
                        modeMenu = 0;

                    }
                    else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.play))&&sourisEvent.bl)
                    {
                        modeJeu = 1;
                        modeMenu = 0;
                        sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
                    }
                    break;
                case 5 :

                    break;
                case 6:

                    break;
                default:
                    break;
            }
            time.timeMenu = time.currentTime;
        }
    }
}

bool testHoverBouton(int sx, int sy, Bouton sprite)
{
    return((sx < sprite.position.x+sprite.lecture[0].w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+sprite.lecture[0].h));
}
