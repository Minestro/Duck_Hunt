#include "main.h"

void initBouton(Bouton &bouton, int ligne)
{
    ligne = ligne * 100;
    bouton.lecture[0].x=0;
    bouton.lecture[0].y=ligne;
    bouton.lecture[0].w=150;
    bouton.lecture[0].h=60;

    bouton.lecture[1].x=200;
    bouton.lecture[1].y=ligne;
    bouton.lecture[1].w=150;
    bouton.lecture[1].h=60;

}
