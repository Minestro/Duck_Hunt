#include "main.h"

void switchSpriteCanard(Canard &canard)
{
    switch (canard.etat)
    {
        case ALIVE:
            if(canard.vecteurPositionY < 0)
            {
                canard.image.lecture.x = (canard.cycleSprite % canard.nbFrames) * canard.pxParFrame;
                canard.cycleSprite = (canard.cycleSprite + 1) % canard.nbFrames;
            }
            else
            {
                canard.image.lecture.x = 0;
            }
            break;
        case TOUCHED: // pas besoin de changer de frame car il n'y a qu'une seule image (pour l'instant)
            break;
        case FREE_FALLING:
            canard.image.lecture.x = (canard.cycleSprite % canard.nbFrames) * canard.pxParFrame;
            canard.cycleSprite = (canard.cycleSprite + 1) % (canard.nbFrames - 1);
           // canard.image.lecture.x+=canard.pxParFrame;
            break;
    }
}
