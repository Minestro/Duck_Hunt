#ifndef SHOT_H
#define SHOT_H

#include "constantes.h"
#include "getEvents.h"
#include "alea.h"
#include "structures.h"

bool testShot(SourisEvent sourisEvent, SDL_Rect lecture, SDL_Rect position);
void shoot(SourisEvent &sourisEvent,Canard &canard, Partie &partie, Time temps, int &modeJeu);
void touched(Canard &canard, Time temps);

#endif // SHOT_H
