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
void charger(Images &i)
{
    i.backGame.image = load_image("sprites/backGame.png");
    i.backGameBlit.image = loadImageWithColorKey("sprites/backGameBlit.png", 0, 0, 0);
    i.duck.image = load_image("sprites/duck.png"); // à découper
    i.hit.image = loadImageWithColorKey("sprites/hit.png", 0, 0, 0);
    i.menu.image = load_image("sprites/menu.png");
    i.points.image = loadImageWithColorKey("sprites/points.png", 0, 0, 0);
    i.shot.image = load_image("sprites/shot.png");
    i.viseur.image = load_image("sprites/viseur.png");
}
