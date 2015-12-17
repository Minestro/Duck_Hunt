#ifndef IMAGES_H
#define IMAGES_H

#include "main.h"
#include "structures.h"

SDL_Surface *load_image(std::string);
SDL_Surface *loadImageWithColorKey(std::string, int, int, int);
void chargerImages(Sprites &sprites, Chien &chien, Boutons &boutons);
void libererImages(Sprites &sprites, Chien &chien, Boutons &boutons);

#endif // IMAGES_H
