#include "main.h"



bool escaped(Sprites sprites, Partie partie)
{
    bool continuer = true;
    int i = partie.canardsEnVie % sprites.canardActifs;
    while(continuer && i < NB_MAX_CANARDS)
    {
        continuer = sprites.canard[i].echappe && sprites.canard[i].etat == ALIVE
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

bool canardsMortsRamasses(Partie partie)
{
    bool tousRamasses = true;
    int i = 0;
    while(tousRamasses && i < NB_MAX_CANARDS)
    {
        tousRamasses = partie.canardRamasse[i++];
    }

    return tousRamasses;
}

bool roundTerminee(Sprites sprites, Partie partie)
{
    return canardsMortsRamasses(partie) || escaped(sprites, partie);
}

bool joueurMaladroit(Partie partie)
{
    return partie.shots == 0 && partie.canardsEnVie == NB_MAX_CANARDS;
}

void relancerPartie(Partie &partie, Sprites &sprites)
{
    partie.relancer = false;

    for(int i = partie.round * 2 ; i < partie.round * 2 + 2 ; i++)
    {
        if(partie.hit[i] == HIT_EMPTY)
        {
            partie.hit[i] = HIT_FAILED;
        }
    }

    for (int i = 0; i < sprites.canardActifs; i++)
    {
        partie.canardRamasse[i] = false;
        partie.xChute[i] = NOT_SET;
        sprites.canard[i].type = alea(1, 3);
        initCanard(sprites.canard[i]);
    }

    initTableau(partie.tableauChasse, sprites);

    partie.chienEnChasse = false;
    partie.canardAbbatu = false;
    partie.canardsEnVie = sprites.canardActifs;
    partie.shots = 3;
    partie.round++;
}


