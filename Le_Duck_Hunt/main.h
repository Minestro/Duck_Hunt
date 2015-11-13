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
const int HAUTEUR = 750;
const int LARGEUR = 761;

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

struct Boutons
{
    SDL_Surface *source;
    SDL_Rect position[NB_BOUTON];
    SDL_Rect lecture[2];
};

void menu(Sprite, Sprite, int &modeMenu, int &modeJeu, SDL_Surface *screen, Police)
void showMenu(SDL_Surface *ecran, Sprite, Sprite, int &modeJeu, int &modeMenu);
bool testHover(int, int, Bouton bouton);
void afficherImage(SDL_Surface *ecran);
SDL_Surface *loadImage(string);
SDL_Surface *loadImageWithColorKey(string, int, int, int);

#endif // HEADER_H
