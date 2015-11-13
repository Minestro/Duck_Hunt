#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include "main.h"

using namespace std;

void menu(Sprite background, Sprite bouton, int &modeMenu, int &modeJeu, SDL_Surface *screen, Police police)
{
    bool sortir = false;
    bool bl = false;
    int sx, sy;
    SDL_Event event;
    Uint8 *keystates = SDL_GetKeyState(NULL);
    while (sortir==false)
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
        showMenu(background, bouton, modeJeu, modeMenu);
    }
}


void showMenu(SDL_Surface *ecran, Sprite background, Sprite bouton, int &modeJeu, int &modeMenu)
{
    SDL_BlitSurface(background.source, NULL, ecran, &background.position);

}

bool testHover(int sx, int sy, Sprite sprite)
{
    return((sx < sprite.position.x+sprite.lecture.w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+sprite.lecture.h));
}
