#include "main.h"

using namespace std;

void menu(Sprites sprites, Boutons boutons, int &modeMenu, int &modeJeu, SDL_Surface *ecran, Police police, Uint8 *keystates)
{
    bool sortir = false;
    bool bl = false;
    int sx, sy;
    SDL_Event event;
    while (sortir==false)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type) {
            case SDL_QUIT:
                modeJeu=0;
                sortir=true;
                break;
            case SDL_MOUSEMOTION:
                sx = event.motion.x;
                sy = event.motion.y;
            case SDL_MOUSEBUTTONDOWN :
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    bl = true;
                }
                break;
            case SDL_MOUSEBUTTONUP :
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    bl = false;
                }
            default:
                break;
            }
        }
        keystates = SDL_GetKeyState(NULL);
        switch (modeMenu)
        {
            case 0:
                sortir = true;
            break;
            case 1 :
                showMenu(ecran, sprites, boutons, modeMenu, sx, sy);
                if ((testHoverBouton(sx, sy, boutons.quit))&&bl)
                {
                    modeMenu = 0;

                }
            break;
        }
    }
}

bool testHoverBouton(int sx, int sy, Bouton sprite)
{
    return((sx < sprite.position.x+sprite.lecture[0].w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+sprite.lecture[0].h));
}
