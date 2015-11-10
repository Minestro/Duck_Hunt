#ifndef IMAGES_H
#define IMAGES_H

#define TAILLE_SPRITES 200

#include <SDL/SDL.h>
#include "applySurface.h"

struct Image
{
    SDL_Surface *image;
    SDL_Rect position;
};

struct Images
{
    Image backGame;
    Image backGameBlit;
    Image duck;
    Image hit;
    Image menu;
    Image points;
    Image shot;
    Image viseur;
};


struct Sprites
{
    SDL_Rect sprite[9];
};


Sprites creationSprites();
void charger(Images &i);

#endif // IMAGES_H
