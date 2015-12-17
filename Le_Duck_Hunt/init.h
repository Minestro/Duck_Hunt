#ifndef INIT_H
#define INIT_H

#include "constantes.h"
#include "alea.h"
#include "structures.h"

void initTableau(TableauChasse &tableau, Sprites sprites);
void initFichiers();
void initMessage(Message msgs[]);
void initBouton(Boutons &boutons);
void initSourisEvent(SourisEvent &SourisEvent);
void initTime(Time &time);
void initPartie(Partie &partie, int nbCanards);
void initChien(Chien &chien);
void initCanard(Canard &cn, Partie partie);
void initHighScore(HighScore highScore[]);

#endif // INIT_H
