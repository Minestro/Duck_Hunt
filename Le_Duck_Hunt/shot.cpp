#include "main.h"

bool testShot(SourisEvent sourisEvent, Sprite sprite)
{
    return((sourisEvent.sx < sprite.position.x+sprite.lecture.w)&&(sourisEvent.sx > sprite.position.x)&&(sourisEvent.sy > sprite.position.y)&&(sourisEvent.sy < sprite.position.y+sprite.lecture.h)&&(sourisEvent.bl));
}

bool shot(SourisEvent sourisEvent,Canard &canard)
{
        if (canard.vivant)
        {
            if (testShot(sourisEvent, canard.image))
            {
                canard.vivant = false;
            }
        }
}
