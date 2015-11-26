#include "main.h"

void switchSpriteCanard(Canard &canard)
{
    switch (canard.etat)
    {
    case 2:
        canard.image.lecture.x=(canard.cycleSprite%canard.nbFrames)*canard.pxParFrame;
        canard.cycleSprite = (canard.cycleSprite+1)%canard.nbFrames;
        break;
    case 1:
        canard.image.lecture.x=(canard.cycleSprite%canard.nbFrames)*canard.pxParFrame;
        canard.cycleSprite = (canard.cycleSprite+1)%(canard.nbFrames-1);
        break;
    }
}
