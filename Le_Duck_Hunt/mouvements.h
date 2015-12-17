#ifndef MOUVEMENTS_H
#define MOUVEMENTS_H

#include "main.h"
#include "relancerPartie.h"
#include "alea.h"
#include "structures.h"

void ramasserCanard(Chien &chien, Partie &partie, Sprites sprites);
bool chienDevientHeureux(Chien chien, Partie partie);
void controlesChien(Chien &chien, Partie &partie, Sprites sprites);
void canardSurvivant(Sprites &sprites, Partie &partie, int numeroCanard);
void mouvementsCanard(Canard &canard);
void detectionBordsChien(Chien &chien);
void detectionBordsCanard(Canard &canard, Partie &partie, int i);
void changementDirection(Canard &canard);

#endif // MOUVEMENTS_H
