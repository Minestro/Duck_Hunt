#ifndef MENU_H
#define MENU_H

#include "constantes.h"
#include "show.h"
#include "file.h"
#include "getEvents.h"
#include "init.h"
#include "alea.h"
#include "structures.h"

void menu(SDL_Surface *ecran, Sprites &sprites, Boutons &boutons, int &modeMenu, int &modeJeu, SourisEvent &sourisEvent, Time &time, Message msgs[], Partie &partie, Chien &chien);
bool testHoverBouton(int, int, Bouton, SDL_Rect lecture);

#endif // MENU_H
