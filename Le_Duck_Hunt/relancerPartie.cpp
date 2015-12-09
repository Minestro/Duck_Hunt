#include "main.h"

bool roundTerminee(Partie partie, Canard canard[], int canardActifs)
{
    bool tousMorts = true;
    bool enChute = false;
    for (int i=0; i<canardActifs; i++)
    {
        if (canard[i].etat!=DEAD)
        {
            tousMorts = false;
        }
        if (canard[i].etat==FREE_FALLING)
        {
            enChute = true;
        }
    }
    return (tousMorts || ((partie.shots<=0)&&(!enChute)));
}


void relancerPartie(Partie &partie, Sprites &sprites)
{
    for(int i = partie.round * 2 ; i < partie.round * 2 + 2 ; i++)
    {
        if(partie.hit[i] == HIT_EMPTY)
        {
            partie.hit[i] = HIT_FAILED;
        }
    }

    for (int i = 0; i < sprites.canardActifs; i++)
    {
        sprites.canard[i].type = alea(1, 3);
        initCanard(sprites.canard[i]);
    }

    for (int i = 0 ; i < NB_MAX_CANARDS ; i++)
    {
        partie.xChute[i] = -1;
    }

    partie.canardsEnVie = 2;
    partie.shots = 3;
    partie.round++;
}


