#ifndef STRUCTURES_H
#define STRUCTURES_H

struct HighScore
{
    std::string nom;
    int score;
};

struct TableauChasse
{
    int typeCanard[NB_MAX_CANARDS];
    // si le canard n'est pas récupéré alors la case vaut NOT_SET,
    // sinon, il vaut la valeur de son type
};

struct Message // Une structure pour afficher avec les fontes, par exemple les scores, ou le niveau !
{
    SDL_Color textColor;    //couleur du texte
    int fontSize;   //taille de la police
    std::string message; // le contenu du texte#include "constantes.h"
    SDL_Rect position; //position de l'affichage tu texte
    TTF_Font *font; // police
    SDL_Surface *source; // image-texte à afficher
};

struct Partie
{
    TableauChasse tableauChasse;
    bool relancer;
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
    HighScore highScore[NB_HIGH_SCORE];
    char pseudoT[LONGUEUR_MAX_PSEUDO];
    std::string pseudo;
};

struct Sprite // Peut représenter une image comme une feuille de sprites
{
    SDL_Surface *source;
    SDL_Rect position;
    SDL_Rect lecture;
};

struct Canard
{
    int type; // 0 : noir, 1 : marron, 2 : violet
    int etat; // 0 : mort, 1 : en chute, 2 : touché, 3 : vivant
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
    Uint32 tempsDepuisTir; // On veut savoir combien de ms se sont écoulés depuis le tir pour passer de TOUCHED à FREE_FALLING
};

struct Chien
{
    int vecteurPositionX;
    int vecteurPositionY;
    int etat;

    Sprite image[NOMBRE_IMAGES_CHIEN]; // On va utiliser des feuilles de sprite différentes
    int nbFrames;
    int cycleSprite;

    int vitesseAnimation;
    Uint32 vitesseAnimationTime;

    Uint32 tempsDepuisEtat; // Même principe que tempsDepuisTir mais depuis un certain etat;
    bool devantHerbe; // si on le blit avant ou après les herbes hautes
};

struct Sprites // Rassemble toutes les images et les feuilles de sprite
{
    Sprite background;
    Sprite background_blit;
    Sprite background_menu;

    int canardActifs;
    Canard canard[NB_MAX_CANARDS];

    Sprite hits;
    Sprite shots;
    Sprite viseur;
    Sprite points;
    SDL_Surface *canardSprite[NOMBRE_TYPES];
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
    bool actif;
};

struct Boutons
{
    SDL_Surface *source;
    SDL_Rect lecture[2];
    Bouton bouton[NB_BOUTONS_DIFFERENTS];
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
    Uint32 timeFps;
    Uint32 timeMenu;
    Uint32 timeKey;
    Uint32 timeDefKey;
    int fpsTime, menuTime, keyTime, defKeyTime;
};


#endif // STRUCTURES_H
