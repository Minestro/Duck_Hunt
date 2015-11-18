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

const int HAUTEUR = 761;
const int LARGEUR = 750;
const int BPP = 32;
const int FPS_MAX = 60;

struct Sprite
{
    SDL_Surface *source;
    SDL_Rect position;
    SDL_Rect lecture;
};

struct Sprites
{
    Sprite background;
    Sprite background_blit;
    Sprite background_menu;
    Sprite viseur;
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
    SDL_Rect position;
    SDL_Rect lecture[2];
};

struct Boutons
{
    SDL_Surface *source;
    Bouton play;
    Bouton quit;
};

struct SourisEvent
{
    bool bl;
    bool br;
    bool bm;
    int sx;
    int sy;
};

struct Time
{
    Uint32 currentTime;
    Uint32 timeRefresh;
    int fpsTime;
    Uint32 timeEvents;
    int eventsTime;
};

void menu(Sprites, Boutons, int &modeMenu, int &modeJeu, SDL_Surface *screen, Police, Uint8 *keystates, SourisEvent &sourisEvent, Time &time);
void showMenu(SDL_Surface *ecran, Sprites, Boutons, int &modeMenu, int, int);
bool testHoverBouton(int, int, Bouton);
void genererRendu(SDL_Surface *ecran, Sprites sprites, SourisEvent);
void chargerImages(Sprites &sprites, Boutons &bouton);
void initBouton(Bouton &bouton, int);
void initSourisEvent(SourisEvent &SourisEvent);
void initTime(Time &time);
SDL_Surface *loadImage(std::string);
SDL_Surface *loadImageWithColorKey(std::string, int, int, int);
bool getEvents (SourisEvent &sourisEvent, Uint8 *keystates, Time &time);

#endif // HEADER_H
