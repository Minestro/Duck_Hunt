#include "main.h"

bool testShot(SourisEvent sourisEvent, SDL_Rect lecture, SDL_Rect position)
{
    return((sourisEvent.sx < position.x+lecture.w)&&(sourisEvent.sx > position.x)&&(sourisEvent.sy > position.y)&&(sourisEvent.sy < position.y+lecture.h));
}

void shoot(SourisEvent &sourisEvent,Canard &canard, Partie &partie, Time temps, int &modeJeu)
{
    if (!partie.alreadyGetEvent)
    {
        if(getEvents(sourisEvent, 1))
        {
            modeJeu = 0;
        }
        partie.alreadyGetEvent = true;
    }
    if (sourisEvent.clicGauche && !(partie.shots < 0) && partie.jeu)
    {
        if (!partie.alreadyClic)
        {
            partie.shots--;
            partie.alreadyClic = true;
        }
        if (testShot(sourisEvent, canard.lecture, canard.position)&&(!partie.alreadyShot)&&(canard.etat==ALIVE))
        {
            partie.alreadyShot = true;
            canard.etat = TOUCHED;
            partie.score += (canard.type + 1) * 500;
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
    if (partie.shots < 0)
    {
        partie.shots = 0;
    }
}

void touched(Canard &canard, Time temps)
{
    if(temps.currentTime - canard.tempsDepuisTir > 250) // Si le temps écoulé depuis le tir est plus de un quart de sec, le canard passe de ALIVE à FREE_FALLING
    {
        canard.etat = FREE_FALLING;
        canard.lecture.x = alea(0, 1) * 70;
    }
}

