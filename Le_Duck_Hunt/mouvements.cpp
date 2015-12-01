#include "main.h"

int alea(int mini, int maxi)
{
    return rand() % (++maxi - mini)  + mini;

    //return rand() / (RAND_MAX / (maxi - mini + 1)); // NE PAS EFFACER, J'AI PENSE A UN NOUVEAU MODE DE JEU !
}

void mouvementsCanard(Canard &canard) // mouvement physique et mouvement au niveau de l'animation
{
    canard.image.position.x += canard.vecteurPositionX;
    canard.image.position.y += canard.vecteurPositionY;

    switch (canard.etat)
    {
        case ALIVE:
            if (canard.vecteurPositionY > 2)
            {
                canard.image.lecture.y = 140;
            }
            else
            {
                canard.image.lecture.y = 0;
            }
            if (canard.vecteurPositionX < 0)
            {
                canard.image.lecture.y += 210;
            }
            break;
        case TOUCHED:
            canard.image.lecture.x = 0;
            canard.image.lecture.y = 280;
            break;
        case FREE_FALLING:
            canard.image.lecture.y = 70;
            break;
    }
}

void detectionBords(Canard &canard)
{
    switch(canard.etat)
    {
        case ALIVE:
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
    case FREE_FALLING:
        if (canard.image.position.y+canard.image.lecture.h > HAUTEUR)
        {
            canard.etat = DEAD;
            SDL_FreeSurface(canard.image.source);
        }
    }
}

void changementDirection(Canard &canard)
{
    switch(canard.etat)
    {
        case ALIVE:
            if(alea(0, 100) == 33)
            {
                do
                {
                    canard.vecteurPositionY = alea(-5, 5);
                    if(canard.vecteurPositionY >= 0)
                    {
                        canard.vecteurPositionX = 5 - canard.vecteurPositionY;
                    }
                    else
                    {
                        canard.vecteurPositionX = 5 + canard.vecteurPositionY;
                    }
                }
                while(canard.vecteurPositionX == 0 || canard.vecteurPositionY == 0);
            }
            break;
        case TOUCHED:
            canard.vecteurPositionX = canard.vecteurPositionY = 0;
            break;
        case FREE_FALLING:
            canard.vecteurPositionX = 0;
            canard.vecteurPositionY = 2;
            break;
    }
    detectionBords(canard);
}
