#include "main.h"

void initBouton(Bouton &bouton, int ligne)
{
    ligne = ligne * 100;
    bouton.lecture[0].x = 0;
    bouton.lecture[0].y = ligne;
    bouton.lecture[0].w = 150;
    bouton.lecture[0].h = 60;

    bouton.lecture[1].x = 200;
    bouton.lecture[1].y = ligne;
    bouton.lecture[1].w = 150;
    bouton.lecture[1].h = 60;

}

void initSourisEvent(SourisEvent &sourisEvent)
{
    sourisEvent.bl = sourisEvent.bm = sourisEvent.br = 0;
    sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
}

void initTime(Time &time)
{
    time.fpsTime = (1/(FPS_MAX*1.0)*1000); // Calcule en ms le temps entre chaque actualisation d'image à partir de la constante FPS_LIMIT.
    time.menuTime = 10;
    time.timeMenu = 0;
    time.timeFps = 0;
}

void initCanard(Canard &cn)
{
    switch (cn.type) //type 0 : noir, type 1: marron, type 2: violet
    {
    case 0:
        cn.image.source = loadImageWithColorKey("sprites/canardNoir.png", 228, 255, 0);
        cn.vitesse = 16;
        break;
    case 1:
        cn.image.source = loadImageWithColorKey("sprites/canardMarron.png", 228, 255, 0);
        cn.vitesse = 16;
        break;
    case 2:
        cn.image.source = loadImageWithColorKey("sprites/canardViolet.png", 228, 255, 0);
        cn.vitesse = 8;
        break;
    }
    cn.etat = 2;
    cn.nbFrames = 3;
    cn.pxParFrame = 70;
    cn.cycleSprite = 0;
    cn.vitesseAnimation = 50;
    cn.vitesseTime = cn.vitesseAnimationTime = 0;

    cn.image.lecture.x = 0;
    cn.image.lecture.y = 0;
    cn.image.lecture.w = 70;
    cn.image.lecture.h = 70;
    cn.image.position.x = alea(1,LARGEUR-cn.image.lecture.w);
    cn.image.position.y = alea(1,HAUTEUR-LIMITE_BASSE-cn.image.lecture.h);
    do
    {
        cn.vecteurPositionX = alea(-5,5);
        if(cn.vecteurPositionX >= 0)
        {
            cn.vecteurPositionY = 5 - cn.vecteurPositionX;
        }
        else
        {
            cn.vecteurPositionY = 5 + cn.vecteurPositionX;
        }
    }
    while(cn.vecteurPositionX == 0 || cn.vecteurPositionY == 0);
}
