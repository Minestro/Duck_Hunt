#include "main.h"

void switchSpriteChien(Chien &chien, Partie &partie)
{
    controlesChien(chien, partie);
    switch(chien.etat)
    {
        case CHIEN_MARCHE:
            chien.image[CHIEN_MARCHE].lecture.x = (chien.cycleSprite % chien.nbFrames) * chien.pxParFrame;
            chien.cycleSprite = (chien.cycleSprite + 1) % chien.nbFrames;
            if(partie.chienEnChasse)
            {
                if(
                    (
                        abs((chien.image[CHIEN_MARCHE].position.x + chien.image[CHIEN_MARCHE].lecture.w / 2) - (partie.xChute[(partie.canardsEnVie + 1) % NB_MAX_CANARDS])) < 10
                    )
                  )
                {
                    partie.chienEnChasse = false;
                    partie.canardRamasse[0] = true; // LOURD CODE DE FEUJ
                    partie.canardRamasse[(partie.canardsEnVie + 1) % NB_MAX_CANARDS] = true;
                }
            }
            break;
        case CHIEN_CONTENT:
            if(!chien.devantHerbe)
            {
                if(chien.image[CHIEN_CONTENT].position.x + chien.image[CHIEN_CONTENT].lecture.w <= partie.xChute[(partie.canardsEnVie + 1) % NB_MAX_CANARDS])
                {
                    if(chien.vecteurPositionX < 0)
                    {
                        chien.vecteurPositionX *= -1;
                        chien.image[CHIEN_MARCHE].lecture.y = chien.image[CHIEN_MARCHE].lecture.h;
                    }
                    chien.image[CHIEN_CONTENT].lecture.y = 100;
                }
                else if(chien.image[CHIEN_CONTENT].position.x > partie.xChute[(partie.canardsEnVie + 1) % NB_MAX_CANARDS])
                {
                    if(chien.vecteurPositionX > 0)
                    {
                        chien.vecteurPositionX *= -1;
                        chien.image[CHIEN_MARCHE].lecture.y = 0;
                    }
                    chien.image[CHIEN_CONTENT].lecture.y = 0;
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
                canard.lecture.x = (canard.cycleSprite % canard.nbFrames) * canard.pxParFrame;
                canard.cycleSprite = (canard.cycleSprite + 1) % canard.nbFrames;
            }
            else
            {
                canard.lecture.x = canard.pxParFrame;
            }
            break;
        case TOUCHED: // pas besoin de changer de frame car il n'y a qu'une seule image (pour l'instant)
            break;
        case FREE_FALLING:
            {
                canard.lecture.x = (canard.cycleSprite % canard.nbFrames) * canard.pxParFrame;
                canard.cycleSprite = (canard.cycleSprite + 1) % (canard.nbFrames - 1);
            }
            break;
    }
}
