#include "main.h"

void switchSpriteCanard(Canard &canard)
{
    switch (canard.etat)
    {
    case ALIVE:
        canard.image.lecture.x=(canard.cycleSprite%canard.nbFrames)*canard.pxParFrame;
        canard.cycleSprite = (canard.cycleSprite+1)%canard.nbFrames;
        break;
    case FREE_FALLING:
        canard.image.lecture.x=(canard.cycleSprite%canard.nbFrames)*canard.pxParFrame;
        canard.cycleSprite = (canard.cycleSprite+1)%(canard.nbFrames-1);
       // canard.image.lecture.x+=canard.pxParFrame;
        break;
    }
}
