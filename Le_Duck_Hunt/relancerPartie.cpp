#include "main.h"

bool partieTerminee(const Partie partie)
{
    return (partie.canardsEnVie == 0 || partie.shots == 0);
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

    for (int i = 0; i<sprites.canardActifs; i++)
    {
        if(sprites.canard[i].etat != DEAD)
        {
            SDL_FreeSurface(sprites.canard[i].image.source);
        }
        initCanard(sprites.canard[i]);
        sprites.canard[i].type = alea(1, 3);
    }

    partie.canardsEnVie = 2;
    partie.shots = 3;
    partie.round++;
}
