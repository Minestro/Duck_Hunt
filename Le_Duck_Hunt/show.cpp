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


void showMenu(SDL_Surface *ecran, Sprites sprites, Boutons boutons, int &modeJeu, int &modeMenu, int sx, int sy)
{
    SDL_BlitSurface(sprites.background.source, NULL, ecran, &sprites.background.position);
    sprites.viseur.position.x=sx-(sprites.viseur.source->w/2);
    sprites.viseur.position.y=sy-(sprites.viseur.source->h/2);
    SDL_BlitSurface(sprites.viseur.source, NULL, ecran, &sprites.viseur.position);
    SDL_Flip(ecran);

}

void genererRendu(SDL_Surface *ecran, Sprites sprites)
{
    SDL_FillRect(ecran,&ecran->clip_rect, SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(sprites.background.source, NULL, ecran, &sprites.background.position);
    SDL_Flip(ecran);
}
