#include "main.h"

int alea(int mini, int maxi)
{
    return (rand() % (++maxi - mini))  + mini;
}

bool chienDevientHeureux(Chien chien, Partie partie, Sprites sprites, DimensionsEcran dim)
{
    return (
             (
              (chien.image[CHIEN_MARCHE].position.x > (dim.largeur - chien.image[CHIEN_MARCHE].lecture.h * 2) / 2)
               && chien.devantHerbe
               )
            || (partie.canardAbbatu && !chien.devantHerbe));
}


void controlesChien(Chien &chien, Partie &partie, Sprites sprites, DimensionsEcran dim)
{
    switch (chien.etat)
    {
        case CHIEN_MARCHE:

            chien.image[CHIEN_MARCHE].position.x += chien.vecteurPositionX;
            chien.image[CHIEN_MARCHE].position.y += chien.vecteurPositionY;

            if(partie.chienEnChasse)
            {
                chien.vitesseAnimation = 10;
            }
            else
            {
                chien.vitesseAnimation = 50;
            }

            if(chienDevientHeureux(chien, partie, sprites, dim))
            {
                chien.etat = CHIEN_CONTENT;
                chien.image[CHIEN_CONTENT].position = chien.image[CHIEN_MARCHE].position;
                chien.image[CHIEN_CONTENT].position.y -= 8;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }

            if(joueurMaladroit(partie) && roundTerminee(sprites, partie))
            {
                partie.afficherMsgTransition = true;
                chien.etat = CHIEN_RIGOLE;
                chien.image[CHIEN_RIGOLE].position = chien.image[CHIEN_MARCHE].position;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }
            else if(partie.canardsEnVie == 1 && roundTerminee(sprites, partie))
            {
                partie.afficherMsgTransition = true;
                chien.etat = CHIEN_CONTENT_SIMPLE;
                chien.image[CHIEN_CONTENT_SIMPLE].position = chien.image[CHIEN_MARCHE].position;
                chien.image[CHIEN_CONTENT_SIMPLE].lecture.x = (partie.tableauChasse.typeCanard[0] - 1) * 90;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }
            else if(partie.canardsEnVie == 0 && roundTerminee(sprites, partie))
            {
                partie.afficherMsgTransition = true;
                chien.etat = CHIEN_CONTENT_DOUBLE;
                chien.image[CHIEN_CONTENT_DOUBLE].position = chien.image[CHIEN_MARCHE].position;
                chien.image[CHIEN_CONTENT_DOUBLE].lecture.y = (partie.tableauChasse.typeCanard[0] - 1) * 80;
                chien.image[CHIEN_CONTENT_DOUBLE].lecture.x = (partie.tableauChasse.typeCanard[1] - 1) * 112;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }


            detectionBordsChien(chien, dim);
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
                chien.image[CHIEN_SAUTE_2].position.y = Y_JEU_CHIEN + sprites.background.position.y;
                chien.image[CHIEN_MARCHE].position = chien.image[CHIEN_SAUTE_2].position;
                chien.nbFrames = 4;
                chien.etat = CHIEN_MARCHE;
                chien.devantHerbe = false;
                partie.jeu = true;
            }

            break;

        case CHIEN_RIGOLE:

            if(SDL_GetTicks() - chien.tempsDepuisEtat > 2500)
            {
                partie.afficherMsgTransition = false;
                partie.relancer = true;
                chien.etat = CHIEN_MARCHE;
            }

            break;

        case CHIEN_CONTENT_SIMPLE:

            if(SDL_GetTicks() - chien.tempsDepuisEtat > 2500)
            {
                partie.afficherMsgTransition = false;
                partie.relancer = true;
                chien.etat = CHIEN_MARCHE;
            }
            break;

        case CHIEN_CONTENT_DOUBLE:
            if(SDL_GetTicks() - chien.tempsDepuisEtat > 2500)
            {
                partie.afficherMsgTransition = false;
                partie.relancer = true;
                chien.etat = CHIEN_MARCHE;
            }

            break;

        default:
            break;
    }
}

void canardSurvivant(Canard &canard)
{
    canard.echappe = canard.etat == ALIVE;
}


void mouvementsCanard(Canard &canard) // mouvement physique et mouvement au niveau de l'animation
{
    canard.position.x += canard.vecteurPositionX;
    canard.position.y += canard.vecteurPositionY;

    switch (canard.etat)
    {
        case ALIVE:
            if (canard.vecteurPositionY > 2)
            {
                canard.lecture.y = 140;
            }
            else
            {
                canard.lecture.y = 0;
            }
            if (canard.vecteurPositionX < 0)
            {
                canard.lecture.y += 210;
            }
            break;
        case TOUCHED:
            canard.lecture.x = 0;
            canard.lecture.y = 280;
            break;
        case FREE_FALLING:
            canard.lecture.y = 70;
            break;
    }
}

void detectionBordsChien(Chien &chien, DimensionsEcran dim)
{
    if(chien.image[CHIEN_MARCHE].position.x + chien.image[CHIEN_MARCHE].lecture.w > dim.largeur)
    {
        chien.vecteurPositionX *= -1;
        chien.image[CHIEN_MARCHE].position.x = dim.largeur - chien.image[CHIEN_MARCHE].lecture.w;
        chien.image[CHIEN_MARCHE].lecture.y = 0;
    }
    else if(chien.image[CHIEN_MARCHE].position.x < 0)
    {
        chien.vecteurPositionX *= -1;
        chien.image[CHIEN_MARCHE].position.x = 0;
        chien.image[CHIEN_MARCHE].lecture.y = chien.image[CHIEN_MARCHE].lecture.h;
    }
}



void detectionBordsCanard(Canard &canard, Partie &partie, DimensionsEcran dim, Sprites sprites)
{
    switch(canard.etat)
    {
        case ALIVE:
            if(!canard.echappe)
            {
                if(canard.position.x <= 0)
                {
                    canard.position.x = 0;
                    canard.vecteurPositionX *= -1;
                }
                else if (canard.position.x + canard.lecture.w >= dim.largeur)
                {
                    canard.position.x = dim.largeur - canard.lecture.w;
                    canard.vecteurPositionX *= -1;
                }
                if(canard.position.y <= 0)
                {
                    canard.position.y = 0;
                    canard.vecteurPositionY *= -1;
                }
            }
            if (canard.position.y + canard.lecture.h >= sprites.background.position.y + sprites.background.source->h - LIMITE_BASSE)
            {
                canard.position.y =sprites.background.position.y + sprites.background.source->h - LIMITE_BASSE - canard.lecture.h;
                canard.vecteurPositionY *= -1;
            }
            break;
        case FREE_FALLING:
            if (canard.position.y + canard.lecture.h > sprites.background.position.y + sprites.background.source->h - LIMITE_BASSE + canard.lecture.h)
            {
                canard.etat = DEAD;
                partie.canardsEnVie--;
                partie.canardAbbatu = true;
                partie.chienEnChasse = true;
                sauvegarderPositionX(partie, canard);
            }
            break;
        case DEAD:
            partie.tableauChasse.typeCanard[(partie.canardsEnVie + 1) % 2] = canard.type;
        default:
            break;
    }
}

void sauvegarderPositionX(Partie &partie, Canard canard) // On sauvegarde la position Y à la mort d'un canard pour que le chien puisse le retrouver
{
    partie.xChute[(partie.canardsEnVie + 1) % NB_MAX_CANARDS] = canard.position.x + canard.lecture.w / 2;
}

void changementDirection(Canard &canard)
{
    switch(canard.etat)
    {
        case ALIVE:
            if(alea(0, 100) == 33
                && canard.position.x > 0
                && canard.position.x + canard.lecture.w < LARGEUR
                && canard.position.y > 0
                && canard.position.y + canard.lecture.h < HAUTEUR - LIMITE_BASSE)
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
    }
}
