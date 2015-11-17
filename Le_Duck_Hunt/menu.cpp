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
        showMenu(ecran, sprites, boutons, modeJeu, modeMenu, sx, sy);
    }
}

bool testHover(int sx, int sy, Sprite sprite)
{
    return((sx < sprite.position.x+sprite.lecture.w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+sprite.lecture.h));
}
