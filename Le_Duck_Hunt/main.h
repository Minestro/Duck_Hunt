#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

// Note ! Mets en commentaire le ce define, moi j'en ai besoin pour chez moi

/*#define VIETKHANG
#ifdef VIETKHANG
#include "../DuckHunt/include/SDL/SDL.h"
#include "../DuckHunt/include/SDL/SDL_image.h"
#include "../DuckHunt/include/SDL/SDL_ttf.h"
#else*/
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
//#endif

// Type du canard
#define DARK 1 // Sombre, le plus lent : 500 points.
#define CHESNUT 2 // Noisette, niveau intermédiaire : 1000 points.
#define BLUISH_PURPLE 3 // Violet bleuâtre, un avion de chasse : 1500 points.

// Etats possibles
#define ALIVE 3 // En vie : le canard vole.
#define TOUCHED 2 // Touché : il s'arrête de voler pour dire aurevoir à la vie.
#define FREE_FALLING 1 // En chute libre : il tombe verticalement.
#define DEAD 0 // Mort.

// Hit
#define HIT_OK 2
#define HIT_FAILED 1
#define HIT_EMPTY 0

// Tableau d'images pour les diverses animations du chien
#define CHIEN_MARCHE 0
#define CHIEN_CONTENT 1
#define CHIEN_SAUTE_1 2
#define CHIEN_SAUTE_2 3
#define CHIEN_RIGOLE 4
#define CHIEN_CONTENT_SIMPLE 5
#define CHIEN_CONTENT_DOUBLE 6
#define NOMBRE_IMAGES_CHIEN 7
// Position en Y en fonction de l'état du jeu
#define Y_INTRO_CHIEN 500
#define Y_JEU_CHIEN 440

const int HAUTEUR = 761;
const int LARGEUR = 750;
const int BPP = 32;
const int FPS_MAX = 60;
const int LIMITE_BASSE = 270;
const int NB_MAX_CANARDS = 1000;

const unsigned int VITESSE_N = 35;
const unsigned int VITESSE_M = 30;
const unsigned int VITESSE_V = 25;

struct Message // Une structure pour afficher avec les fontes, par exemple les scores, ou le niveau !
{
    SDL_Color textColor;    //couleur du texte
    int fontSize;   //taille de la police
    std::string message; // le contenu du texte
    SDL_Rect position; //position de l'affichage tu texte
    TTF_Font *font;
};

struct Partie
{
    int canardsEnVie;
    int shots;
    Uint32 temps; //pour un certain mode de jeu
    int round;
    int score;
    int hit[10];
    bool roundJoue[5];
    bool canardAbbatu;
    bool chienCheck;
};

struct Sprite // Peut représenter une image comme une feuille de sprites
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
    int type; // 0 : noir, 1 : marron, 2 : violet
    int nbFrames;
    int pxParFrame;
    int cycleSprite;
    int vecteurPositionY;
    int vecteurPositionX;
    int etat; // 0 : mort, 1 : en chute, 2 : touché, 3 : vivant
    Uint32 tempsDepuisTir; // On veut savoir combien de ms se sont écoulés depuis le tir pour passer de TOUCHED à FREE_FALLING
};

struct Chien
{
    int vecteurPositionX;
    int vecteurPositionY;
    int etat;
    Sprite image[NOMBRE_IMAGES_CHIEN]; // On va utiliser des feuilles de sprite différentes
    int nbFrames;
    int vitesseAnimation;
    Uint32 vitesseAnimationTime;
    int vitesse;
    Uint32 vitesseTime;
    int pxParFrame;
    int cycleSprite;
    Uint32 tempsDepuisEtat; // Même principe que tempsDepuisTir mais depuis un certain etat;
    bool devantHerbe; // si on le blit avant ou après les herbes hautes
};

struct Sprites // Rassemble toutes les images et les feuilles de sprite
{
    Sprite background;
    Sprite background_blit;
    Sprite background_menu;

    Chien chien;

    int canardActifs;
    Canard canard[NB_MAX_CANARDS];

    Sprite hits;
    Sprite shots;
    Sprite viseur;
    Sprite points;
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
    bool clicGauche;
    bool clicDroit;
    bool clicMolette;
};

struct Time
{
    Uint32 currentTime;
    Uint32 timeMenu;
    Uint32 timeFps;
    int fpsTime, menuTime;
};

void menu(Sprites, Boutons, int &modeMenu, int &modeJeu, SourisEvent &sourisEvent, Time &time, Message message);
void showMenu(Sprites, Boutons, int &modeMenu, int, int);
bool testHoverBouton(int, int, Bouton);
void genererRendu(Sprites sprites, SourisEvent sourisEvent, Partie partie, Chien chien);
void chargerImages(Sprites &sprites);
void initBouton(Boutons &boutons);
void initSourisEvent(SourisEvent &SourisEvent);
void initTime(Time &time);
void initCanard(Canard &cn);
void initChien(Chien &chien);
void initMessage(Message &message);
SDL_Surface *loadImage(std::string);
SDL_Surface *loadImageWithColorKey(std::string, int, int, int);
bool getEvents (SourisEvent &sourisEvent);
void changementDirection(Canard &canard);
void detectionBordsChien(Chien &chien);
void mouvementsCanard(Canard &canard);
void switchSpriteCanard(Canard &canard);
int alea(int, int);
void detectionBordsCanard(Canard &canard, Partie &partie);
void shoot(SourisEvent &sourisEvent,Canard &canard, Partie &partie, int i, int canardsActifs, Time temps);
bool testShot(SourisEvent sourisEvent, Sprite sprite);
void touched(Canard &canard, Time temps, Sprite &points);
void showMessage(Message &msg, std::string contenuMessage);
void initPartie(Partie &partie, int nbCanards);
bool partieTerminee(const Partie partie);
void relancerPartie(Partie &partie, Sprites &sprites);
void controlesChien(Chien &chien, Partie &partie);
void switchSpriteChien(Chien &chien, Partie &partie);
void afficherChien(Chien chien);
std::string intToString (int number);

#endif // HEADER_H
