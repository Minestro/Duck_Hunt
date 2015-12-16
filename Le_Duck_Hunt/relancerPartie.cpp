#include "main.h"

bool escaped(Sprites sprites, Partie partie)
{
    bool continuer = true;
    int i = 0;
    while(continuer && i < sprites.canardActifs)
    {
        continuer = partie.tableauChasse.typeCanard[i] == DUCK_ESCAPED;
        i++;
    }
    return continuer;
}

bool canardsMortsRamasses(Partie partie)
{
    bool tousRamasses = true;
    int i = 0;
    while(tousRamasses && i < NB_MAX_CANARDS)
    {
        tousRamasses = (partie.tableauChasse.typeCanard[i] != DUCK_ESCAPED) && (partie.tableauChasse.typeCanard[i] != NOT_SET);
        i++;
    }
    return tousRamasses;
}

bool roundTerminee(Sprites sprites, Partie partie)
{
    bool tableauChasseRempli = true;
    int i = 0;
    while(tableauChasseRempli && i < sprites.canardActifs)
    {
        tableauChasseRempli = partie.tableauChasse.typeCanard[i++] != NOT_SET;
    }

    return tableauChasseRempli || escaped(sprites, partie);
}

bool joueurMaladroit(Partie partie)
{
    return partie.shots == 0 && partie.canardsEnVie == NB_MAX_CANARDS;
}


bool finPartie(Partie partie)
{
    int nbHits = 0;
    for (int i=0; i<10; i++)
    {
        if (partie.hit[i] == 2)
        {
            nbHits++;
        }
    }
    return (nbHits<6);
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
        partie.canardRamasse[i] = false;
        partie.xChute[i] = NOT_SET;
        sprites.canard[i].type = alea(0, 3);
        initCanard(sprites.canard[i], partie);
    }

    initTableau(partie.tableauChasse, sprites);

    partie.chienEnChasse = partie.canardAbbatu = partie.relancer = false;
    partie.canardsEnVie = sprites.canardActifs;
    partie.shots = 3;
    partie.round++;
}


