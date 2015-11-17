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
    SDL_ShowCursor(0);
    SDL_BlitSurface(sprites.background_menu.source, NULL, ecran, &sprites.background.position);
    sprites.viseur.position.x=sx-(sprites.viseur.source->w/2);
    sprites.viseur.position.y=sy-(sprites.viseur.source->h/2);
    SDL_BlitSurface(sprites.viseur.source, NULL, ecran, &sprites.viseur.position);
    boutons.play.position.x=100;
    boutons.play.position.y=100;
    boutons.play.lecture.y=0;
    boutons.play.lecture.w=150;
    boutons.play.lecture.h=60;
    if (testHover(sx, sy, boutons)){
        boutons.play.position.x=200;
    } else {
        boutons.play.position.x=0;
    }
    SDL_BlitSurface(boutons.source, NULL, ecran, &boutons.play.position);
    SDL_Flip(ecran);

}

void genererRendu(SDL_Surface *ecran, Sprites sprites)
{
    SDL_ShowCursor(0);
    SDL_BlitSurface(sprites.background.source, NULL, ecran, &sprites.background.position);
    SDL_BlitSurface(sprites.background_blit.source, NULL, ecran, &sprites.background.position);
    SDL_Flip(ecran);
}
