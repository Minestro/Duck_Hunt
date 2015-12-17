#include "alea.h"

/****************** Nom de la fonction ****************************
* alea                                                            *
******************** Auteur , Dates *******************************
* Nom : LE HO                                                     *
********************* Description *********************************
* Génére la couleur aléatoire des canards                         *
*********************** Entrées ***********************************
* ES: nombre min et max de canards                                *
*******************************************************************/

int alea(int mini, int maxi)
{
    return (rand() % (++maxi - mini))  + mini;
}
