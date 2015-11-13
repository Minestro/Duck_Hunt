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

const int NB_BOUTON = 2;

struct Sprite
{
    SDL_Surface *source;
    SDL_Rect position;
    SDL_Rect lecture;
};

struct Police
{
    TTF_Font *fonts;
    SDL_Color textColor;
    int fontSize;
    std::string police;
};

struct Bouton
{
    SDL_Surface *source;
    SDL_Rect position[NB_BOUTON];
    SDL_Rect lecture[2];
};

void showMenu(SDL_Surface *ecran, Sprite, Sprite int &modeMenu);
bool testHover(int, int, Bouton bouton);
void afficherImage(SDL_Surface *ecran);

#endif // HEADER_H
