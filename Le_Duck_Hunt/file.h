#ifndef FILE_H
#define FILE_H

#include "main.h"
#include "structures.h"

bool testHighScore (std::string fichier, Partie &partie);
void getScore (std::string fichier, HighScore HighScore[]);
void addScore (std::string fichier, std::string nom, int score, HighScore highScore[]);
void echangerTabHS(HighScore highScore[], int pos1, int pos2);
int separer(HighScore highscore[], int debut, int fin);
void triScore (HighScore highScore[],  int debut, int fin);

#endif // FILE_H
