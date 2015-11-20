#include "main.h"

void switchSprite(Sprite &sprite, int nbFrames, int pxParFrame, int &cycleSprite)
{
        sprite.lecture.x=(cycleSprite%nbFrames)*pxParFrame;
        cycleSprite = (cycleSprite+1)%nbFrames;
}
