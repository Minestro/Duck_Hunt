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
#define CHESNUT 2 // Noisette, niveau interm�diaire : 1000 points.
#define BLUISH_PURPLE 3 // Violet bleu�tre, un avion de chasse : 1500 points.

// Etats possibles

/*#define ESCAPING 4 // IL s'enfuit !*/
// J'ai pens� � rajout� un attribut de type bool�en dans la structure Canard plut�t :p

#define ALIVE 3 // En vie : le canard vole.
#define TOUCHED 2 // Touch� : il s'arr�te de voler pour dire aurevoir � la vie.
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

// Position en Y en fonction de l'�tat du jeu
#define Y_INTRO_CHIEN 500
#define Y_JEU_CHIEN 440

//Les differents messages
#define MSG_SCORE 0
#define MSG_PAUSE 1
#define MSG_NIVEAU 2
#define MSG_BOUTONS 3

//Pour les valeurs d'un tableau
#define NOT_SET -1
#define TO_RESET -2

const int HAUTEUR = 761;
const int LARGEUR = 750;
const int BPP = 16;
const int FPS_MAX = 60;
const int LIMITE_BASSE = 270;
const int NB_MAX_CANARDS = 2;

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
    SDL_Surface *source;
};

struct Partie
{
    bool jeu;
    bool chienEnChasse;
    int canardsEnVie;
    int shots;
    Uint32 temps; //pour un certain mode de jeu
    int round;
    int niveau;
    int score;
    int hit[10];
    bool alreadyShot;
    bool alreadyGetEvent;
    bool alreadyClic;
    bool canardAbbatu;
    int xChute[NB_MAX_CANARDS];
    bool canardRamasse[NB_MAX_CANARDS];
};

struct Sprite // Peut repr�senter une image comme une feuille de sprites
{
    SDL_Surface *source;
    SDL_Rect position;
    SDL_Rect lecture;
};

struct Canard
{
    int type; // 0 : noir, 1 : marron, 2 : violet
    int etat; // 0 : mort, 1 : en chute, 2 : touch�, 3 : vivant
    bool echappe;

    int vecteurPositionY;
    int vecteurPositionX;

    SDL_Rect lecture;
    SDL_Rect position;

    int vitesseAnimation;
    Uint32 vitesseAnimationTime;

    int vitesse;
    Uint32 vitesseTime;

    int nbFrames;
    int cycleSprite;
    Uint32 tempsDepuisTir; // On veut savoir combien de ms se sont �coul�s depuis le tir pour passer de TOUCHED � FREE_FALLING
};

struct Chien
{
    int vecteurPositionX;
    int vecteurPositionY;
    int etat;

    Sprite image[NOMBRE_IMAGES_CHIEN]; // On va utiliser des feuilles de sprite diff�rentes
    int nbFrames;
    int cycleSprite;

    int vitesseAnimation;
    Uint32 vitesseAnimationTime;

    Uint32 tempsDepuisEtat; // M�me principe que tempsDepuisTir mais depuis un certain etat;
    bool devantHerbe; // si on le blit avant ou apr�s les herbes hautes
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
    SDL_Surface *canardSprite[3];
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
    std::string contenu;
};

struct Boutons
{
    SDL_Surface *source;
    SDL_Rect lecture[2];
    Bouton play;
    Bouton quit;
    Bouton reprendre;
};

struct SourisEvent
{
    bool bl, bl2;
    bool br, br2;
    bool bm, bm2;
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

bool getEvents(SourisEvent &sourisEvent, bool);

void genererRendu(SDL_Surface *ecran, Sprites sprites, SourisEvent sourisEvent, Partie partie, Chien chien);
void showChien(SDL_Surface *ecran, Chien chien);
void showPointsCanard(SDL_Surface *ecran, Canard canard, Sprite &points);
void showMessage(SDL_Surface *ecran, Message &msg, std::string contenuMessage);
void showMenu(SDL_Surface *ecran, Sprites sprites, Boutons boutons, int &modeMenu, Message msgs[], int sx, int sy);

void menu(SDL_Surface *ecran, Sprites, Boutons, int &modeMenu, int &modeJeu, SourisEvent &sourisEvent, Time &time, Message msgs[], Partie partie);
bool testHoverBouton(int, int, Bouton, SDL_Rect lecture);

bool munitionsEpuisees(Partie partie);
bool escaped(Sprites sprites, Partie partie);
bool roundTerminee(Sprites sprites, Partie partie);
bool canardsMortsRamasses(Partie partie);
bool joueurMaladroit(Partie partie);

bool transitionRound(Chien &chien);
void relancerPartie(Partie &partie, Sprites &sprites);
void initPartie(Partie &partie, int nbCanards);
void initBouton(Boutons &boutons);
void initSourisEvent(SourisEvent &SourisEvent);
void initTime(Time &time);
void initCanard(Canard &cn);
void initChien(Chien &chien);
void initMessage(Message msgs[]);

SDL_Surface *loadImage(std::string);
SDL_Surface *loadImageWithColorKey(std::string, int, int, int);
void chargerImages(Sprites &sprites);

void changementDirection(Canard &canard);
void mouvementsCanard(Canard &canard);
void detectionBordsCanard(Canard &canard, Partie &partie, SDL_Surface *canardSprite[]);
void switchSpriteCanard(Canard &canard);
void sauvegarderPositionX(Partie &partie, Canard canard);
void shoot(SourisEvent &sourisEvent,Canard &canard, Partie &partie, Time temps, int &modeJeu);
bool testShot(SourisEvent sourisEvent, SDL_Rect lecture, SDL_Rect position);
void touched(Canard &canard, Time temps);
void canardSurvivant(Canard &canard);

void controlesChien(Chien &chien, Partie &partie);
bool chienDevientHeureux(Chien chien, Partie partie);
void detectionBordsChien(Chien &chien);
void switchSpriteChien(Chien &chien, Partie &partie);

int alea(int mini, int maxi);
std::string intToString (int number);

#endif // HEADER_H
