#ifndef SHOW_H
#define SHOW_H

#include "constantes.h"
#include "menu.h"
#include "structures.h"

void genererRendu(SDL_Surface *ecran, Sprites sprites, SourisEvent sourisEvent, Partie partie, Chien chien, Message msgs[]);
void showChien(SDL_Surface *ecran, Chien chien);
void showPointsCanard(SDL_Surface *ecran, Canard canard, Sprite &points);
void showMessage(SDL_Surface *ecran, Message &msg);
void showMenu(SDL_Surface *ecran, Sprites sprites, Boutons &boutons, int &modeMenu, Message msgs[], Partie partie, int sx, int sy);
void showPoints(Message msgs[], SDL_Surface *ecran, Partie partie);
void showBouton(SDL_Surface *ecran, Boutons &boutons, Message msgs[], int boutonNom, int sx, int sy);
std::string intToString (int number);

#endif // SHOW_H
