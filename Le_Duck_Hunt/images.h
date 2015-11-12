#ifndef IMAGES_H
#define IMAGES_H

#define TAILLE_SPRITES 200
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <sstream>
#include <iostream>

using namespace std;

struct Image
{
    // L'image en elle-même
    SDL_Surface *image;
    // Position de l'image
    Uint16 x;
    Uint16 y;
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

SDL_Surface *chargerUneImage(string nomFichier);
void charger(Images &i);
void placer(Images &i);
void libererImages(Images i);

#endif // IMAGES_H
