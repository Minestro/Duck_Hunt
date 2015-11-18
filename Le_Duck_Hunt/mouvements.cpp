#include "main.h"

void mouvementsCanard(CanardNoir &canard)
{
    canard.image.position.x += canard.vecteurPositionX;
    canard.image.position.y += canard.vecteurPositionY;
}

void changementDirection(CanardNoir &canard, SDL_Event *ev)
{
    if(ev->motion.x > canard.image.position.x and ev->motion.x < canard.image.position.x + canard.image.source->w
            and ev->motion.y > canard.image.position.y and ev->motion.y < canard.image.position.y + canard.image.source->h)
    {
        if(ev->type == SDL_MOUSEBUTTONDOWN)
        {
            exit(EXIT_SUCCESS);

        }
    }


    if(SDL_GetTicks() % 222 == 0)
    {
        canard.vecteurPositionX = ((SDL_GetTicks() % 17) % 10) - 5;
        if(canard.vecteurPositionX >= 0)
        {
            canard.vecteurPositionY = 5 - canard.vecteurPositionX;
        }
        else
        {
            canard.vecteurPositionY = 5 + canard.vecteurPositionX;
        }
    }

    if(canard.image.position.x < 0 or canard.image.position.x + canard.image.lecture.w > LARGEUR)
    {
        canard.vecteurPositionX *= -1;
    }
    if(canard.image.position.y < 0 or canard.image.position.y + canard.image.lecture.h > HAUTEUR - 360)
    {
        canard.vecteurPositionY *= -1;
    }

    if(canard.vecteurPositionX == 0 or canard.vecteurPositionY == 0)
    {
        canard.vecteurPositionX = SDL_GetTicks() % 10 - 5;
        if(canard.vecteurPositionX >= 0)
        {
            canard.vecteurPositionY = 5 - canard.vecteurPositionX;
        }
        else
        {
            canard.vecteurPositionY = 5 + canard.vecteurPositionX;
        }
    }
}
