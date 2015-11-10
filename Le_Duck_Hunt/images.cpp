#include "images.h"

/*** Une fonction qui définit découpe en quelques sortes une feuille de sprites ***/
/*** Par exemple, Sprite numéro 2 correspond au rectangle en haut à droite dans une feuille de carrés 3*3 ***/
Sprites creationSprites()
{
    Sprites s;

    int i, k;

    for(i = 0 ; i < 3 ; i++)
    {
        for(k = 0 ; k < 3 ; k++)
        {
            s.sprite[k + i * 3].x = k * TAILLE_SPRITES;
            s.sprite[k + i * 3].y = i * TAILLE_SPRITES;
            s.sprite[k + i * 3].w = TAILLE_SPRITES;
            s.sprite[k + i * 3].h = TAILLE_SPRITES;
        }
    }
    return s;
}

/*** fonction qui charge les images ***/
void charger(Images* i)
{
    i->licenceCC = loadImageWithColorKey("images/licence.bmp", 10, 10, 10); // La seule image que je n'ai pas faite : prise sur Wikipedia
    i->spritesTouchesUn = loadImageWithColorKey("images/spritesTouchesUn.bmp", 10, 10, 10);
    i->spritesTouchesDeux = loadImageWithColorKey("images/spritesTouchesDeux.bmp", 10, 10, 10);
    i->commandes = loadImageWithColorKey("images/commandes.bmp", 10, 10, 10);
    i->letsPong = loadImageWithColorKey("images/letsPong.bmp", 10, 10, 10);
    i->essayer = loadImageWithColorKey("images/essayez.bmp", 10, 10, 10);
    i->GO = loadImageWithColorKey("images/GO.bmp", 10, 10, 10);
    i->bienvenue = loadImageWithColorKey("images/bienvenue.bmp", 10, 10, 10);
    i->presentation = loadImageWithColorKey("images/presentation.bmp", 10, 10, 10);
    // Pour ceux qui vont jouer beaucoup à mon jeu, il ne faut pas qu'ils se lassent
    if(SDL_GetTicks() % 2 == 0) // SDL_GetTicks renvoie le nombre de ms depuis l'initiation de la SDL
    {
        i->astuce = loadImageWithColorKey("images/astuce.bmp", 10, 10, 10);
    }
    else
    {
        i->astuce = loadImageWithColorKey("images/astuce2.bmp", 10, 10, 10);
    }
}

/*** Des BlitSurface en masse pour coller les images, faites par moi même avec PhotoFiltre ***/
void applySpritesIntro(ConstantesPong contexte, Sprites s, Images i, Pong jeu)
{
    applySurface((contexte.largeurEcran - i.bienvenue->w) / 2,
                contexte.hauteurBordure + 30,
                i.bienvenue,
                jeu.ecran, NULL);
    applySurface((contexte.largeurEcran - i.presentation->w) / 2,
                (contexte.hauteurEcran - i.presentation->h) / 2,
                i.presentation,
                jeu.ecran, NULL);
}

void applySpritesPostIntro(ConstantesPong contexte, Sprites s, Images i, Pong jeu)
{
    applySurface((contexte.largeurEcran - i.essayer->w) / 2,
                contexte.hauteurBordure + 30,
                i.essayer,
                jeu.ecran, NULL);

    if(jeu.clavier.touche[SDLK_q])
    {
        applySurface(contexte.largeurEcran / 2 - TAILLE_SPRITES,
                contexte.Y_Init_Un + 50,
                i.spritesTouchesUn,
                jeu.ecran, &s.sprite[1]);
    }
    else if(jeu.clavier.touche[SDLK_a])
    {
        applySurface(contexte.largeurEcran / 2 - TAILLE_SPRITES,
                contexte.Y_Init_Un + 50,
                i.spritesTouchesUn,
                jeu.ecran, &s.sprite[2]);
    }
    else if(jeu.clavier.touche[SDLK_s] and !jeu.clavier.touche[SDLK_a]
            and !jeu.clavier.touche[SDLK_q])
    {
        applySurface(contexte.largeurEcran / 2 - TAILLE_SPRITES,
                contexte.Y_Init_Un + 50,
                i.spritesTouchesUn,
                jeu.ecran, &s.sprite[4]);
    }
    else
    {
        applySurface(contexte.largeurEcran / 2 - TAILLE_SPRITES,
                contexte.Y_Init_Un + 50,
                i.spritesTouchesUn,
                jeu.ecran, &s.sprite[0]);
    }

    if(jeu.clavier.touche[SDLK_a] and jeu.clavier.touche[SDLK_q])
    {
        applySurface(contexte.largeurEcran / 2 - TAILLE_SPRITES,
                contexte.Y_Init_Un + 50,
                i.spritesTouchesUn,
                jeu.ecran, &s.sprite[3]);
    }


    if(jeu.clavier.touche[SDLK_KP_MINUS])
    {
        applySurface(contexte.largeurEcran / 2,
                contexte.Y_Init_Deux + 50,
                i.spritesTouchesDeux,
                jeu.ecran, &s.sprite[1]);
    }
    else if(jeu.clavier.touche[SDLK_KP_PLUS])
    {
        applySurface(contexte.largeurEcran / 2,
                contexte.Y_Init_Deux + 50,
                i.spritesTouchesDeux,
                jeu.ecran, &s.sprite[2]);
    }
    else if(jeu.clavier.touche[SDLK_KP9] and !jeu.clavier.touche[SDLK_KP_PLUS]
            and !jeu.clavier.touche[SDLK_KP_MINUS])
    {
        applySurface(contexte.largeurEcran / 2,
                contexte.Y_Init_Deux + 50,
                i.spritesTouchesDeux,
                jeu.ecran, &s.sprite[4]);
    }
    else
    {
        applySurface(contexte.largeurEcran / 2,
                contexte.Y_Init_Deux + 50,
                i.spritesTouchesDeux,
                jeu.ecran, &s.sprite[0]);
    }

    if(jeu.clavier.touche[SDLK_KP_MINUS] and jeu.clavier.touche[SDLK_KP_PLUS])
    {
        applySurface(contexte.largeurEcran / 2,
                contexte.Y_Init_Deux + 50,
                i.spritesTouchesDeux,
                jeu.ecran, &s.sprite[3]);
    }


    applySurface((contexte.largeurEcran - i.commandes->w) / 2,
                contexte.Y_Init_Un + TAILLE_SPRITES,
                i.commandes,
                jeu.ecran, NULL);

    applySurface(((contexte.largeurEcran - i.astuce->w) / 2),
                contexte.hauteurEcran - contexte.hauteurBordure - i.astuce->h,
                i.astuce, jeu.ecran, NULL);
}

void applySpritesPostIntroDeux(ConstantesPong contexte, Sprites s, Images i, Pong jeu)
{
    applySurface((contexte.largeurEcran - i.letsPong->w) / 2,
                contexte.hauteurBordure + 30,
                i.letsPong,
                jeu.ecran, NULL);

    applySurface((contexte.largeurEcran - i.licenceCC->w) / 2,
                contexte.Y_Init_Un + TAILLE_SPRITES,
                i.licenceCC,
                jeu.ecran, NULL);

    applySurface(((contexte.largeurEcran - i.astuce->w) / 2),
                contexte.hauteurEcran - contexte.hauteurBordure - i.astuce->h,
                i.astuce, jeu.ecran, NULL);
}

void applySpritesOwr(ConstantesPong contexte, Sprites s, Images i, Pong jeu)
{
    applySurface((contexte.largeurEcran - i.GO->w) / 2,
                contexte.hauteurBordure + 30,
                i.GO,
                jeu.ecran, NULL);
}

