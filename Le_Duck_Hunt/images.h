#ifndef IMAGES_H
#define IMAGES_H

#include "constantes.h"
#include "structures.h"

SDL_Surface *load_image(std::string);
SDL_Surface *loadImageWithColorKey(std::string, int, int, int);
void chargerImages(Sprites &sprites, Chien &chien, Boutons &boutons, std::string theme);
void libererImages(Sprites &sprites, Chien &chien, Boutons &boutons);

#endif // IMAGES_H
