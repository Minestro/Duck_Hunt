#include "main.h"

bool testShot(SourisEvent sourisEvent, Sprite sprite)
{
    return((sourisEvent.sx < sprite.position.x+sprite.lecture.w)&&(sourisEvent.sx > sprite.position.x)&&(sourisEvent.sy > sprite.position.y)&&(sourisEvent.sy < sprite.position.y+sprite.lecture.h)&&(sourisEvent.clicGauche));
}

void shot(SourisEvent sourisEvent,Canard &canard, int &shots)
{
        switch(canard.etat)
        {
            case 2:
            if (sourisEvent.clicGauche)
            {
                std::cout << shots << std::endl;
                shots--;
                if (testShot(sourisEvent, canard.image))
                {
                    chute(canard);
                    canard.etat = 1;
                }
            }
            break;
        }
}
