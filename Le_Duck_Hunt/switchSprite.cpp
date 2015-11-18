#include "main.h"

void switchSprite(Canard &cn)
{
    if(cn.vecteurPositionY < 0)
    {
        switch(SDL_GetTicks() % 3)
        {
            case 0:
                cn.image.lecture.x = 0;
                break;
            case 1:
                cn.image.lecture.x = 70;
                break;
            case 3:
                cn.image.lecture.x = 140;
                break;
            default:
                break;
        }

    }
}
