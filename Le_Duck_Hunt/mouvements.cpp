#include "main.h"

int alea(int mini, int maxi)
{
    return (rand() % (++maxi - mini))  + mini;

   // return rand() / (RAND_MAX / (maxi - mini + 1)); // NE PAS EFFACER, J'AI PENSE A UN NOUVEAU MODE DE JEU !
}


void controlesChien(Chien &chien, Partie &partie)
{
    switch (chien.etat)
    {
        case CHIEN_MARCHE:
            detectionBordsChien(chien);
            chien.image[CHIEN_MARCHE].position.x += chien.vecteurPositionX;
            chien.image[CHIEN_MARCHE].position.y += chien.vecteurPositionY;
            if(partie.chienEnChasse)
            {
                chien.vitesseAnimation = 50;
            }
            else
            {
                chien.vitesseAnimation = 100;
            }

            if((((chien.image[CHIEN_MARCHE].position.x > (LARGEUR - chien.image[CHIEN_MARCHE].lecture.h * 2) / 2) && chien.devantHerbe))
                || (partie.canardAbbatu && chien.image[CHIEN_MARCHE].position.y == Y_JEU_CHIEN))
            {
                chien.etat = CHIEN_CONTENT;
                chien.image[CHIEN_CONTENT].position = chien.image[CHIEN_MARCHE].position;
                chien.image[CHIEN_CONTENT].position.y -= 8;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }
            break;
        case CHIEN_CONTENT:
            if(SDL_GetTicks() - chien.tempsDepuisEtat > 750 && !partie.canardAbbatu)
            {
                if(chien.devantHerbe)
                {
                    chien.etat = CHIEN_SAUTE_1;
                }
                else
                {
                    chien.etat  = CHIEN_MARCHE;
                }
                chien.image[CHIEN_SAUTE_1].position.x = chien.image[CHIEN_CONTENT].position.x + chien.image[CHIEN_SAUTE_1].lecture.w / 2;
                chien.image[CHIEN_SAUTE_1].position.y = chien.image[CHIEN_CONTENT].position.y - chien.image[CHIEN_SAUTE_1].lecture.h / 2;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }
            else
            {
                partie.canardAbbatu = false;
            }

            if(SDL_GetTicks() - chien.tempsDepuisEtat > 750 && partie.canardAbbatu)
            {
                chien.etat--;
                partie.canardAbbatu = false;
            }
            break;
        case CHIEN_SAUTE_1:
            if(SDL_GetTicks() - chien.tempsDepuisEtat > 100)
            {
                chien.image[CHIEN_SAUTE_1].position.x += 5;
                chien.etat = CHIEN_SAUTE_2;
                chien.image[CHIEN_SAUTE_2].position = chien.image[CHIEN_SAUTE_1].position;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }
            break;
        case CHIEN_SAUTE_2:
            if(SDL_GetTicks() - chien.tempsDepuisEtat > 100)
            {
                chien.image[CHIEN_SAUTE_2].position.y = Y_JEU_CHIEN;
                chien.image[CHIEN_MARCHE].position = chien.image[CHIEN_SAUTE_2].position;
                chien.nbFrames = 4;
                chien.pxParFrame = chien.image[CHIEN_MARCHE].lecture.w;
                chien.etat = CHIEN_MARCHE;
                chien.devantHerbe = false;
            }
            break;
        case CHIEN_RIGOLE:
            break;
        case CHIEN_CONTENT_SIMPLE:
            break;
        case CHIEN_CONTENT_DOUBLE:
            break;
    }
}


void mouvementsCanard(Canard &canard) // mouvement physique et mouvement au niveau de l'animation
{
    canard.image.position.x += canard.vecteurPositionX;
    canard.image.position.y += canard.vecteurPositionY;

    switch (canard.etat)
    {
        case ALIVE:
            if (canard.vecteurPositionY > 2)
            {
                canard.image.lecture.y = 140;
            }
            else
            {
                canard.image.lecture.y = 0;
            }
            if (canard.vecteurPositionX < 0)
            {
                canard.image.lecture.y += 210;
            }
            break;
        case TOUCHED:
            canard.image.lecture.x = 0;
            canard.image.lecture.y = 280;
            break;
        case FREE_FALLING:
            canard.image.lecture.y = 70;
            break;
    }
}

void detectionBordsChien(Chien &chien)
{
    if(chien.image[CHIEN_MARCHE].position.x + chien.image[CHIEN_MARCHE].lecture.w > LARGEUR)
    {
        chien.vecteurPositionX *= -1;
        chien.image[CHIEN_MARCHE].position.x = LARGEUR - chien.image[CHIEN_MARCHE].lecture.w;
        chien.image[CHIEN_MARCHE].lecture.y = 0;
    }
    else if(chien.image[CHIEN_MARCHE].position.x < 0)
    {
        chien.vecteurPositionX *= -1;
        chien.image[CHIEN_MARCHE].position.x = 0;
        chien.image[CHIEN_MARCHE].lecture.y = chien.image[CHIEN_MARCHE].lecture.h;
    }
}



void detectionBordsCanard(Canard &canard, Partie &partie)
{
    switch(canard.etat)
    {
        case ALIVE:
            if(canard.image.position.x <= 0)
            {
                canard.image.position.x = 0;
                canard.vecteurPositionX *= -1;
            }
            else if (canard.image.position.x + canard.image.lecture.w >= LARGEUR)
            {
                canard.image.position.x = LARGEUR - canard.image.lecture.w;
                canard.vecteurPositionX *= -1;
            }
            if(canard.image.position.y <= 0 )
            {
                canard.image.position.y = 0;
                canard.vecteurPositionY *= -1;
            }
            else if (canard.image.position.y + canard.image.lecture.h >= HAUTEUR - LIMITE_BASSE)
            {
                canard.image.position.y = HAUTEUR-LIMITE_BASSE-canard.image.lecture.h;
                canard.vecteurPositionY *= -1;
            }
            break;
        case FREE_FALLING:
            if (canard.image.position.y + canard.image.lecture.h > HAUTEUR - LIMITE_BASSE + canard.image.lecture.h)
            {
                canard.etat = DEAD;
                SDL_FreeSurface(canard.image.source);
                SDL_FreeSurface(canard.points.source);
                partie.canardsEnVie--;
                partie.canardAbbatu = true;
                partie.chienEnChasse = true;
                sauvegarderPositionX(partie, canard);
                SDL_FreeSurface(canard.points.source);
                SDL_FreeSurface(canard.image.source);
            }
            break;
        default:
            break;
    }
}

void sauvegarderPositionX(Partie &partie, Canard canard) // On sauvegarde la position Y à la mort d'un canard pour que le chien puisse le retrouver
{
    int i = 0;
    bool sauvegarde = partie.xChute[i] == -1;
    while(!sauvegarde && i < NB_MAX_CANARDS - 1)
    {
        i++;
        sauvegarde = partie.xChute[i] == -1;
    }
    partie.xChute[i] = canard.image.position.x + canard.image.lecture.w / 2;
}

void changementDirection(Canard &canard)
{
    switch(canard.etat)
    {
        case ALIVE:
            if(alea(0, 100) == 33)
            {
                do
                {
                    canard.vecteurPositionY = alea(-10, 10);
                    if(canard.vecteurPositionY >= 0)
                    {
                        canard.vecteurPositionX = 10 - canard.vecteurPositionY;
                    }
                    else
                    {
                        canard.vecteurPositionX = 10 + canard.vecteurPositionY;
                    }
                }
                while(canard.vecteurPositionX == 0 || canard.vecteurPositionY == 0);
            }
            break;
        case TOUCHED:
            canard.vecteurPositionX = canard.vecteurPositionY = 0;
            break;
        case FREE_FALLING:
            canard.vecteurPositionX = 0;
            canard.vecteurPositionY = 7;
            break;
        case DEAD: // Inutile puisqu'on SDL_FreeSurface à leur mort ?
            canard.vecteurPositionX = 0;
            canard.vecteurPositionY = 0;
            break;
    }
}
