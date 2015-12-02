#include "main.h"

void relancerPartie(Partie &partie, Sprites &sprites)
{
        // Beaucoup de simplification de code à faire à mon avis.
    if(partie.canardsEnVie == 0)
    {
        for (int i = 0; i < sprites.canardActifs; i++)
        {
            sprites.canard[i].type = alea(1, 3);
            initCanard(sprites.canard[i]);
        }
        partie.canardsEnVie = 2;
        partie.shots = 3;
        partie.round++;
    }

    if(partie.shots == 0)
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
        }
        partie.shots = 3;

        for (int i = 0; i<sprites.canardActifs; i++)
        {
            sprites.canard[i].type = alea(1, 3);
            initCanard(sprites.canard[i]);
        }
        partie.canardsEnVie = 2;
        partie.shots = 3;
        partie.round++;
    }
}
