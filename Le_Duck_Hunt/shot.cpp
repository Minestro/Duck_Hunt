#include "main.h"

bool testShot(SourisEvent sourisEvent, Sprite sprite)
{
    return((sourisEvent.sx < sprite.position.x+sprite.lecture.w)&&(sourisEvent.sx > sprite.position.x)&&(sourisEvent.sy > sprite.position.y)&&(sourisEvent.sy < sprite.position.y+sprite.lecture.h));
}

void shoot(SourisEvent &sourisEvent,Canard &canard, Partie &partie, int i, int canardsActifs, Time temps)
{
    if((canard.etat == ALIVE && sourisEvent.clicGauche && ((i >= canardsActifs - 1)||(testShot(sourisEvent, canard.image)))) && partie.shots != 0 && partie.canardsEnVie != 0)
    {
        sourisEvent.clicGauche = false;
        partie.shots--;
        if (testShot(sourisEvent, canard.image))
        {
            canard.etat = TOUCHED;
            partie.score += canard.type * 500;
            canard.tempsDepuisTir = temps.currentTime;
            if(partie.hit[partie.round * 2] == HIT_EMPTY)
            {
                partie.hit[partie.round * 2] = HIT_OK;
            }
            else
            {
                partie.hit[partie.round * 2 + 1] = HIT_OK;
            }
        }
    }
}

void touched(Canard &canard, Time temps)
{
    if(temps.currentTime - canard.tempsDepuisTir > 250) // Si le temps écoulé depuis le tir est plus de un quart de sec, le canard passe de ALIVE à FREE_FALLING
    {
        canard.etat = FREE_FALLING;
    }
}
