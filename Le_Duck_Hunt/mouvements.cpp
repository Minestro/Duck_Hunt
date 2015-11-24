#include "main.h"

int alea(int mini, int maxi)
{
    maxi++;
    return rand()%(maxi-mini) +mini;
}

void mouvementsCanard(Canard &canard)
{
    canard.image.position.x += canard.vecteurPositionX;
    canard.image.position.y += canard.vecteurPositionY;
    if (canard.vecteurPositionY>2)
    {
        canard.image.lecture.y=140;
    } else {
        canard.image.lecture.y=0;
    }
    if (canard.vecteurPositionX < 0)
    {
        canard.image.lecture.y+=210;
    }
}

void detectionBords(Canard &canard)
{
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
}
void changementDirection(Canard &canard)
{
    if(alea(0,75)==33)
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
    }

    if(canard.vecteurPositionX == 0 or canard.vecteurPositionY == 0)
    {
        canard.vecteurPositionX = alea(0,5);
        if(canard.vecteurPositionX >= 0)
        {
            canard.vecteurPositionY = 5 - canard.vecteurPositionX;
        }
        else
        {
            canard.vecteurPositionY = 5 + canard.vecteurPositionX;
        }
    }
    detectionBords(canard);
}
