#include "main.h"

bool testShot(SourisEvent sourisEvent, Sprite sprite)
{
    return((sourisEvent.sx < sprite.position.x+sprite.lecture.w)&&(sourisEvent.sx > sprite.position.x)&&(sourisEvent.sy > sprite.position.y)&&(sourisEvent.sy < sprite.position.y+sprite.lecture.h));
}

void shot(SourisEvent &sourisEvent,Canard &canard, int &shots, int i, int canardsActifs)
{
    switch(canard.etat)
    {
    case 2:
        if (sourisEvent.clicGauche)
        {
            if ((i >= canardsActifs-1)||(testShot(sourisEvent, canard.image)))
            {
                shots--;
                sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
                if (testShot(sourisEvent, canard.image))
                {
                    canard.etat = 1;
                }
            }
        }
        break;
    }
}
