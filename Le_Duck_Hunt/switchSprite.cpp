#include "main.h"

void switchSpriteChien(Chien &chien, Partie &partie)
{
    controlesChien(chien, partie);
    switch(chien.etat)
    {
        case CHIEN_MARCHE:
            chien.image[CHIEN_MARCHE].lecture.x = (chien.cycleSprite % chien.nbFrames) * chien.pxParFrame;
            chien.cycleSprite = (chien.cycleSprite + 1) % chien.nbFrames;
            break;
        case CHIEN_CONTENT:
            if(!chien.devantHerbe)
            {
                if(chien.image[CHIEN_CONTENT].position.x > partie.xChute[partie.canardsEnVie % NB_MAX_CANARDS])
                {
                    chien.image[CHIEN_CONTENT].lecture.y = 0;
                }
                else
                {
                    chien.image[CHIEN_CONTENT].lecture.y = 100;
                }
            }
            else
            {
                chien.image[CHIEN_CONTENT].lecture.y = 100;
            }
            break;
        default:
            break;
    }
}

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
           // if(SDL_GetTicks() % 1000 < 500) /// Il faudra que tu m'aides à implémenter ça : je veux que l'animation de la chute du canard soit plus lente
            {
                canard.image.lecture.x = (canard.cycleSprite % canard.nbFrames) * canard.pxParFrame;
                canard.cycleSprite = (canard.cycleSprite + 1) % (canard.nbFrames - 1);
            }
            break;
    }
}
