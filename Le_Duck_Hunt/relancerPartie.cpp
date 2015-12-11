 #include "main.h"

bool escaped(Sprites sprites)
{
    bool continuer = true;
    int i = 0;
    while(continuer && i < NB_MAX_CANARDS)
    {
        continuer = sprites.canard[i].echappe
                    && (
                          sprites.canard[i].position.x + sprites.canard[i].lecture.w < 0
                       || sprites.canard[i].position.x > LARGEUR
                       || sprites.canard[i].position.y + sprites.canard[i].lecture.h < 0
                       || sprites.canard[i].position.y > HAUTEUR - LIMITE_BASSE

                            );
        i++;
    }

    return continuer;
}

bool munitionsEpuisees(Partie partie)
{
    return partie.shots == 0;
}

bool roundTerminee(Partie partie)
{
    bool tousRamasses = true;
    int i = 0;
    while(tousRamasses && i < NB_MAX_CANARDS)
    {
        tousRamasses = partie.canardRamasse[i++];
    }


    return tousRamasses;
}


void relancerPartie(Partie &partie, Sprites &sprites)
{
    for(int i = 0 ; i < NB_MAX_CANARDS ; i++)
    {
        partie.canardRamasse[i] = false;
        partie.xChute[i] = NOT_SET;
    }

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

    partie.chienEnChasse = false;
    partie.canardAbbatu = false;
    partie.canardsEnVie = 2;
    partie.shots = 3;
    partie.round++;
}


