#include "main.h"

void switchSprite(Canard &cn)
{
    if(cn.vecteurPositionY < 0)
    {
        cn.image.lecture.x=(cn.cycleSprite%3)*70;
        cn.cycleSprite = (cn.cycleSprite+1)%3;
    }
}
