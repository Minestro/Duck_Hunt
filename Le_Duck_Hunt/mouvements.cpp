#include "mouvements.h"
#include "alea.h"

void ramasserCanard(Chien &chien, Partie &partie, Sprites sprites)
{
    bool present = false;
    int rechercheNotSet = -1;
    while(!present && rechercheNotSet < sprites.canardActifs)
    {
        rechercheNotSet++;
        present = partie.tableauChasse.typeCanard[rechercheNotSet] == NOT_SET;
    }

    switch(chien.etat)
    {
        case CHIEN_MARCHE:
            if(partie.chienEnChasse)
            {
                if(
                    (
                        abs((chien.image[CHIEN_MARCHE].position.x + chien.image[CHIEN_MARCHE].lecture.w / 2) - (partie.xChute[rechercheNotSet])) < 10
                    )
                  )
                {
                    partie.chienEnChasse = partie.xChute[1] != NOT_SET;
                    partie.tableauChasse.typeCanard[rechercheNotSet] = sprites.canard[rechercheNotSet].type;
                    for(int j = 0 ; j < rechercheNotSet ; j++)
                    {
                        partie.canardRamasse[j] = true;
                    }
                }
            }
            break;
        case CHIEN_CONTENT:
            if(chien.image[CHIEN_CONTENT].position.x <= partie.xChute[rechercheNotSet])
            {
                if(chien.vecteurPositionX < 0)
                {
                    chien.vecteurPositionX *= -1;
                    chien.image[CHIEN_MARCHE].lecture.y = chien.image[CHIEN_MARCHE].lecture.h;
                }
                chien.image[CHIEN_CONTENT].lecture.y = 100;
            }
            break;
    }
}

bool chienDevientHeureux(Chien chien, Partie partie)
{
    return (
             (

              (chien.image[CHIEN_MARCHE].position.x > (LARGEUR - chien.image[CHIEN_MARCHE].lecture.h * 2) / 2)
               && chien.devantHerbe
              )
            || (partie.canardAbbatu && !chien.devantHerbe));

}

void controlesChien(Chien &chien, Partie &partie, Sprites sprites)
{
    switch (chien.etat)
    {
        case CHIEN_MARCHE:

            chien.image[CHIEN_MARCHE].position.x += chien.vecteurPositionX;
            chien.image[CHIEN_MARCHE].position.y += chien.vecteurPositionY;

            if(partie.chienEnChasse)
            {
                chien.vitesseAnimation = 30;
            }
            else
            {
                chien.vitesseAnimation = 80;
            }

            if(chienDevientHeureux(chien, partie))
            {
                chien.etat = CHIEN_CONTENT;
                chien.image[CHIEN_CONTENT].position = chien.image[CHIEN_MARCHE].position;
                chien.image[CHIEN_CONTENT].position.y -= 8;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }

            if(joueurMaladroit(partie) && roundTerminee(sprites, partie))
            {
                chien.etat = CHIEN_RIGOLE;
                chien.image[CHIEN_RIGOLE].position = chien.image[CHIEN_MARCHE].position;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }
            else if(partie.canardsEnVie == 1 && roundTerminee(sprites, partie))
            {
                chien.etat = CHIEN_CONTENT_SIMPLE;
                chien.image[CHIEN_CONTENT_SIMPLE].position = chien.image[CHIEN_MARCHE].position;

                if(partie.tableauChasse.typeCanard[0] > NOT_SET) // Si il y a un type d'affecté <-- --> si la case correspond à un type de canard ramassé
                {
                    chien.image[CHIEN_CONTENT_SIMPLE].lecture.x = (partie.tableauChasse.typeCanard[0]) * 90;
                }
                else
                {
                    chien.image[CHIEN_CONTENT_SIMPLE].lecture.x = (partie.tableauChasse.typeCanard[1]) * 90;
                }

                chien.tempsDepuisEtat = SDL_GetTicks();
            }
            else if(partie.canardsEnVie == 0 && roundTerminee(sprites, partie))
            {
                chien.etat = CHIEN_CONTENT_DOUBLE;
                chien.image[CHIEN_CONTENT_DOUBLE].position = chien.image[CHIEN_MARCHE].position;
                chien.image[CHIEN_CONTENT_DOUBLE].lecture.y = (partie.tableauChasse.typeCanard[0]) * 80;
                chien.image[CHIEN_CONTENT_DOUBLE].lecture.x = (partie.tableauChasse.typeCanard[1]) * 112;
                chien.tempsDepuisEtat = SDL_GetTicks();
            }

            detectionBordsChien(chien);
            break;

        case CHIEN_CONTENT:

            if(SDL_GetTicks() - chien.tempsDepuisEtat > 600 && !partie.canardAbbatu)
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

            if(SDL_GetTicks() - chien.tempsDepuisEtat > 200 && partie.canardAbbatu)
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
                chien.etat = CHIEN_MARCHE;
                chien.devantHerbe = false;
                partie.jeu = true;
            }

            break;

        case CHIEN_RIGOLE:

            if(SDL_GetTicks() - chien.tempsDepuisEtat > 2500)
            {
                partie.relancer = true;
                chien.etat = CHIEN_MARCHE;
            }

            break;

        case CHIEN_CONTENT_SIMPLE:

            if(SDL_GetTicks() - chien.tempsDepuisEtat > 2500)
            {
                partie.relancer = true;
                chien.etat = CHIEN_MARCHE;
            }
            break;

        case CHIEN_CONTENT_DOUBLE:
            if(SDL_GetTicks() - chien.tempsDepuisEtat > 2500)
            {
                partie.relancer = true;
                chien.etat = CHIEN_MARCHE;
            }

            break;

        default:
            break;
    }
}

void canardSurvivant(Sprites &sprites, Partie &partie, int numeroCanard)
{
    sprites.canard[numeroCanard].echappe = sprites.canard[numeroCanard].etat == ALIVE;
    if((
                partie.tableauChasse.typeCanard[numeroCanard] == NOT_SET)
        && (
            sprites.canard[numeroCanard].position.x + sprites.canard[numeroCanard].lecture.w < 0
            || sprites.canard[numeroCanard].position.x > LARGEUR
            || sprites.canard[numeroCanard].position.y + sprites.canard[numeroCanard].lecture.h < 0
            || sprites.canard[numeroCanard].position.y > HAUTEUR - LIMITE_BASSE
        ) && sprites.canard[numeroCanard].echappe)
    {
        partie.tableauChasse.typeCanard[numeroCanard] = DUCK_ESCAPED;
    }
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



void detectionBordsCanard(Canard &canard, Partie &partie, int i)
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
                else if (canard.position.x + canard.lecture.w >= LARGEUR)
                {
                    canard.position.x = LARGEUR - canard.lecture.w;
                    canard.vecteurPositionX *= -1;
                }
                if(canard.position.y <= 0)
                {
                    canard.position.y = 0;
                    canard.vecteurPositionY *= -1;
                }
            }
            if (canard.position.y + canard.lecture.h >= HAUTEUR - LIMITE_BASSE)
            {
                canard.position.y = HAUTEUR-LIMITE_BASSE-canard.lecture.h;
                canard.vecteurPositionY *= -1;
            }
            break;
        case FREE_FALLING:
            if (canard.position.y + canard.lecture.h > HAUTEUR - LIMITE_BASSE + canard.lecture.h)
            {
                canard.etat = DEAD;
                partie.canardsEnVie--;
                partie.canardAbbatu = true;
                partie.chienEnChasse = true;
                partie.xChute[i] = canard.position.x + canard.lecture.w / 2;
            }
            break;
        case DEAD:
        default:
            break;
    }
}

void changementDirection(Canard &canard)
{
    switch(canard.etat)
    {
        case ALIVE:
            if(alea(0, 100) == 42
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
