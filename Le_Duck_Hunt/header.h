#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>

void showMenu(int &modeMenu);
//bool testHover(int sx, int sy, Bouton bouton);

struct Sprite
{
    SDL_Surface *source;
    SDL_Rect position;
    SDL_Rect lecture;
};

#endif // HEADER_H
