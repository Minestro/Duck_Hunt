#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


// Contexte
#define HAUTEUR 761
#define LARGEUR 750
#define BPP 16
#define FPS_MAX 60
#define LIMITE_BASSE 270

// Constantes jeu
#define NB_MAX_CANARDS 2
#define NB_BOUTONS_DIFFERENTS 10
#define NOMBRE_MESSAGES 11
#define NB_HIGH_SCORE 10
#define LONGUEUR_MAX_PSEUDO 11
#define NB_CANARDS_POUR_GAGNER 6

#define VITESSE_N 30
#define VITESSE_M 25
#define VITESSE_B 20
#define VITESSE_V 15

// Type du canard
#define DARK 0 // Noir, ne pas toucher.
#define CHESNUT 1 // Noisette, le plus lent : 500 points.
#define BLOOD 2 // Rouge, niveau intermédiaire : 1000 points.
#define BLUISH_PURPLE 3 // Violet bleuâtre, un avion de chasse : 1500 points.
#define NOMBRE_TYPES 4

// Etats possibles

#define ALIVE 3 // En vie : le canard vole.
#define TOUCHED 2 // Touché : il s'arrête de voler pour dire aurevoir à la vie.
#define FREE_FALLING 1 // En chute libre : il tombe verticalement.
#define DEAD 0 // Mort.

// Hit
#define HIT_OK 2
#define HIT_FAILED 1
#define HIT_EMPTY 0

// Tableau d'images pour les diverses animations du chien
#define CHIEN_MARCHE 0
#define CHIEN_CONTENT 1
#define CHIEN_SAUTE_1 2
#define CHIEN_SAUTE_2 3
#define CHIEN_RIGOLE 4
#define CHIEN_CONTENT_SIMPLE 5
#define CHIEN_CONTENT_DOUBLE 6
#define NOMBRE_IMAGES_CHIEN 7

// Position en Y en fonction de l'état du jeu
#define Y_INTRO_CHIEN 500
#define Y_JEU_CHIEN 440

//Les differents messages
#define MSG_SCORE 0
#define MSG_PAUSE 1
#define MSG_NIVEAU 2
#define MSG_BOUTONS 3
#define MSG_0_TOUCHE 4
#define MSG_1_TOUCHE 5
#define MSG_2_TOUCHE 6
#define MSG_TABLEAU_SCORE 7
#define MSG_TEXTE 8
#define MSG_SCORE_ROUGE 9
#define MSG_PSEUDO 10

//Les différents noms des boutons
#define BOUTON_PLAY 0
#define BOUTON_QUIT 1
#define BOUTON_REPRENDRE 2
#define BOUTON_SCORE 3
#define BOUTON_OPTIONS 4
#define BOUTON_MODE_CLASSIQUE 5
#define BOUTON_MODE_DEUX 6
#define BOUTON_RETOUR 7
#define BOUTON_OK 8

//Pour les valeurs d'un tableau
#define NOT_SET -1
#define TO_RESET -2
#define DUCK_ESCAPED -3

#endif // HEADER_H
