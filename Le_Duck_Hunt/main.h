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

struct Canard
{
    Sprite image;
    int vitesseAnimation;
    Uint32 vitesseAnimationTime;
    int vitesse;
    Uint32 vitesseTime;
    int type;
    int typeAnimation; //Vol, tombe ou bat des ailes
    int nbFrames;
    int pxParFrame;
    int cycleSprite;
    int vecteurPositionY;
    int vecteurPositionX;
};

struct Chien
{
    // a remplir sur le modèle de canard
};

struct Sprites
{
    Sprite background;
    Sprite background_blit;
    Sprite background_menu;

    Chien chien;
    Canard canard;

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
    Uint32 timeMenu;
    Uint32 timeFps;
    int fpsTime, menuTime;
};

void menu(Sprites, Boutons, int &modeMenu, int &modeJeu, SDL_Surface *screen, SourisEvent &sourisEvent, Time &time);
void showMenu(SDL_Surface *ecran, Sprites, Boutons, int &modeMenu, int, int);
bool testHoverBouton(int, int, Bouton);
void genererRendu(SDL_Surface *ecran, Sprites sprites, SourisEvent sourisEvent);
void chargerImages(Sprites &sprites, Boutons &bouton);
void initBouton(Bouton &bouton, int);
void initSourisEvent(SourisEvent &SourisEvent);
void initTime(Time &time);
void initCanard(Canard &cn);
SDL_Surface *loadImage(std::string);
SDL_Surface *loadImageWithColorKey(std::string, int, int, int);
bool getEvents (SourisEvent &sourisEvent);
void changementDirection(Canard &canard);
void mouvementsCanard(Canard &canard);
void switchSprite(Sprite &sprite, int, int, int &cycleSprite);

#endif // HEADER_H
