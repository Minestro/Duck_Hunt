#include "main.h"

bool partieTerminee(const Partie partie)
{
    bool tousMorts = true;
    int i = 0;
    while(tousMorts && i < NB_MAX_CANARDS)
    {
        tousMorts = partie.xChute[i++] == TO_RESET;
    }
    return tousMorts;
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
        if(sprites.canard[i].etat != DEAD)
        {
            SDL_FreeSurface(sprites.canard[i].image.source);
            SDL_FreeSurface(sprites.canard[i].points.source);
        }
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


