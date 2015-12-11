 #include "main.h"

bool roundTerminee(Partie partie, Canard canard[], int canardActifs)
{
    bool tousRamasses = true;
    int i = 0;
    while(tousRamasses && i < NB_MAX_CANARDS)
    {
        tousRamasses = partie.canardRamasse[i++];
    }
    for(int f = 0 ; f < NB_MAX_CANARDS ; f++)
    {
     //   std::cout << f << " : " << partie.canardRamasse[f] << std::endl;
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


