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
const int LIMITE_BASSE = 270;
const int NB_MAX_CANARDS = 100;


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
    int nbFrames;
    int pxParFrame;
    int cycleSprite;
    int vecteurPositionY;
    int vecteurPositionX;
    int etat; // 0 : mort, 1 : en chute, 2 : vivant
};

struct Chien
{
    Sprite image;
    int vitesseAnimation;
    Uint32 vitesseAnimationTime;
    int vitesse;
    Uint32 vitesseTime;
    int nbFrames;
    int pxParFrame;
    int cycleSprite;
};

struct Sprites
{
    Sprite background;
    Sprite background_blit;
    Sprite background_menu;

    Chien chien;
    int canardActifs;
    Canard canard[NB_MAX_CANARDS];

    Sprite shots;
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
    int clicGauche;
    int clicDroit;
    int clicMolette;
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
void genererRendu(SDL_Surface *ecran, Sprites sprites, SourisEvent sourisEvent, int shots);
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
int alea(int, int);
void detectionBords(Canard &canard);
void shot(SourisEvent sourisEvent, Canard &canard, int &shots);
bool testShot(SourisEvent sourisEvent, Sprite sprite);
void chute(Canard &canard);

#endif // HEADER_H
