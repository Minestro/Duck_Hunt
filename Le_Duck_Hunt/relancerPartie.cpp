#include "relancerPartie.h"


/****************** Nom de la fonction ****************************
* escaped                                                         *
******************** Auteur , Dates *******************************
* Nom : LE HO                                                     *
********************* Description *********************************
* Vérifie que tous les canards ce sont échappés                   *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/


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

/****************** Nom de la fonction ****************************
* canardsMortsRamasses                                            *
******************** Auteur , Dates *******************************
* Nom : LE HO                                                     *
********************* Description *********************************
* Vérifie que le chien à ramasser tous les canards morts          *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/


bool canardsMortsRamasses(Partie partie)
{
    bool tableauChasseRempli = true;
    int i = 0;
    while(tableauChasseRempli && i < 2)
    {
        tableauChasseRempli = partie.tableauChasse.typeCanard[i++] != NOT_SET;
    }

    return tableauChasseRempli;
}

bool roundTerminee(Sprites sprites, Partie partie)
{
    return canardsMortsRamasses(partie) || escaped(sprites, partie);
}

bool joueurMaladroit(Partie partie)
{
    return partie.shots == 0 && partie.canardsEnVie == NB_MAX_CANARDS;
}

/****************** Nom de la fonction ****************************
* finPartie                                                       *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* Permet le passage au round suivant                              *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/

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

/****************** Nom de la fonction ****************************
* relancerPartie                                                  *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* Permet de relancer la partie                                    *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/

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
