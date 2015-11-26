#include "main.h"

int alea(int mini, int maxi)
{
   return rand() % (++maxi - mini)  + mini;

   // return rand() / (RAND_MAX / (maxi - mini + 1)); NE PAS EFFACER, J'AI PENSE A UN NOUVEAU MODE DE JEU !
}

void mouvementsCanard(Canard &canard)
{
    canard.image.position.x += canard.vecteurPositionX;
    canard.image.position.y += canard.vecteurPositionY;
}

void detectionBords(Canard &canard)
{
    switch(canard.etat)
    {
    case 1:
        if (canard.image.position.y > HAUTEUR)
        {
            canard.etat = 0;
        }
        break;
    case 2:
        if(canard.image.position.x <= 0)
        {
            canard.image.position.x = 0;
            canard.vecteurPositionX *= -1;
        }
        else if (canard.image.position.x + canard.image.lecture.w >= LARGEUR)
        {
            canard.image.position.x = LARGEUR - canard.image.lecture.w;
            canard.vecteurPositionX *= -1;
        }
        if(canard.image.position.y <= 0 )
        {
            canard.image.position.y = 0;
            canard.vecteurPositionY *= -1;
        }
        else if (canard.image.position.y + canard.image.lecture.h >= HAUTEUR - LIMITE_BASSE)
        {
            canard.image.position.y = HAUTEUR-LIMITE_BASSE-canard.image.lecture.h;
            canard.vecteurPositionY *= -1;
        }
        break;
    }
}
void changementDirection(Canard &canard)
{
    switch(canard.etat)
    {
    case 1:
        canard.vecteurPositionX = 0;
        canard.vecteurPositionY = 5;
        break;
    case 2:
        if(alea(0,75) == 33)
        {
            do
            {
                canard.vecteurPositionX = alea(-5,5);
                if(canard.vecteurPositionX >= 0)
                {
                    canard.vecteurPositionY = 5 - canard.vecteurPositionX;
                }
                else
                {
                    canard.vecteurPositionY = 5 + canard.vecteurPositionX;
                }
            } while(canard.vecteurPositionX == 0 || canard.vecteurPositionY == 0);
        }
        break;
    }
    detectionBords(canard);
}
