#include "main.h"

bool testShot(SourisEvent sourisEvent, SDL_Rect lecture, SDL_Rect position)
{
    return((sourisEvent.sx < position.x+lecture.w)&&(sourisEvent.sx > position.x)&&(sourisEvent.sy > position.y)&&(sourisEvent.sy < position.y+lecture.h));
}

void shoot(SourisEvent &sourisEvent,Canard &canard, Partie &partie, int i, int canardsActifs, Time temps)
{
    if((canard.etat == ALIVE && sourisEvent.clicGauche && ((i >= canardsActifs - 1)||(testShot(sourisEvent, canard.lecture, canard.position)))) && partie.shots != 0 && partie.canardsEnVie != 0)
    {
        sourisEvent.clicGauche = false;
        partie.shots--;
        if (testShot(sourisEvent, canard.lecture, canard.position))
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

