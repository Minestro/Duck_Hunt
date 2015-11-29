#include "main.h"

bool testShot(SourisEvent sourisEvent, Sprite sprite)
{
    return((sourisEvent.sx < sprite.position.x+sprite.lecture.w)&&(sourisEvent.sx > sprite.position.x)&&(sourisEvent.sy > sprite.position.y)&&(sourisEvent.sy < sprite.position.y+sprite.lecture.h));
}

void shoot(SourisEvent &sourisEvent,Canard &canard, int &shots, int i, int canardsActifs)
{
    if(canard.etat == ALIVE && sourisEvent.clicGauche && ((i >= canardsActifs-1)||(testShot(sourisEvent, canard.image))))
    {
        shots--;
        sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
        if (testShot(sourisEvent, canard.image))
        {
            canard.etat = TOUCHED;
            canard.tempsDepuisTir = SDL_GetTicks();
        }
    }
}

void touched(Canard &canard)
{
    if(SDL_GetTicks() - canard.tempsDepuisTir > 250) // Si le temps écoulé depuis le tir est plus de un quart de sec, le canard passe de ALIVE à FREE_FALLING
    {
        canard.etat = FREE_FALLING;
    }
}
