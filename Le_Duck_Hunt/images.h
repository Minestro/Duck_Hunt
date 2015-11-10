#ifndef IMAGES_H
#define IMAGES_H

#define TAILLE_SPRITES 200

#include <SDL/SDL.h>
#include "applySurface.h"
#include "pong.h"

struct Images
{
    SDL_Surface *spritesTouchesUn;
    SDL_Surface *spritesTouchesDeux;
    SDL_Surface *commandes;
    SDL_Surface *letsPong;
    SDL_Surface *astuce;
    SDL_Surface *essayer;
    SDL_Surface *GO;
    SDL_Surface *bienvenue;
    SDL_Surface *presentation;
    SDL_Surface *licenceCC;
};


struct Sprites
{
    SDL_Rect sprite[9];
};

Sprites creationSprites();
void charger(Images *i);

void applySpritesIntro(ConstantesPong contexte, Images i, Pong jeu);
void applySpritesPostIntro(ConstantesPong contexte, Images i, Pong jeu);
void applySpritesPostIntroDeux(ConstantesPong contexte, Sprites s, Images i, Pong jeu);
void applySpritesOwr(ConstantesPong contexte, Images i, Pong jeu);

#endif // IMAGES_H
