#ifndef RELANCERPARTIE_H
#define RELANCERPARTIE_H

#include "main.h"
#include "alea.h"
#include "init.h"
#include "structures.h"

bool escaped(Sprites sprites, Partie partie);
bool canardsMortsRamasses(Partie partie);
bool roundTerminee(Sprites sprites, Partie partie);
bool joueurMaladroit(Partie partie);
bool finPartie(Partie partie);
void relancerPartie(Partie &partie, Sprites &sprites);

#endif // RELANCERPARTIE_H
