#include "main.h"


void initMessage(Message &message)
{
    message.fontSize = 35;
    message.textColor.r = 255;
    message.textColor.g = 255;
    message.textColor.b = 255;
}

void initBouton(Boutons &boutons)
{
    boutons.source = loadImageWithColorKey("sprites/boutons.bmp", 0, 0, 0);
    boutons.play.contenu = "Jouer";
    boutons.quit.contenu = "Quitter";
    for(int i = 0 ; i < 2 ; i++)
    {
        boutons.lecture[i].x = i * 226;
        boutons.lecture[i].y = 0;
        boutons.lecture[i].w = 216;
        boutons.lecture[i].h = 74;
    }
}

void initSourisEvent(SourisEvent &sourisEvent)
{
    sourisEvent.bl = sourisEvent.bm = sourisEvent.br = false;
    sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
}

void initTime(Time &time)
{
    time.fpsTime = (1/(FPS_MAX*1.0)*1000); // Calcule en ms le temps entre chaque actualisation d'image à partir de la constante FPS_LIMIT.
    time.menuTime = 10;
    time.timeMenu = 0;
    time.timeFps = 0;
    time.currentTime = SDL_GetTicks();
}

void initPartie(Partie &partie, int nbCanards)
{
    partie.chienCheck = false;
    partie.canardAbbatu = false;
    partie.shots = 3;
    partie.canardsEnVie = nbCanards;
    partie.round = partie.score = 0;
    for (int i = 0;  i < 10; i++)
    {
        partie.hit[i] = HIT_EMPTY;
    }
    for (int i = 0 ; i < 5 ; i++)
    {
        partie.roundJoue[i] = false;
    }
}

void initChien(Chien &chien)
{
    chien.devantHerbe = true;
    chien.vecteurPositionX = 10;
    chien.vecteurPositionY = 0;
    chien.pxParFrame = 120;
    chien.cycleSprite = 0;
    chien.vitesseAnimation = 100; // Plus cette valeur est élevée, plus l'animation est lente...
    chien.vitesseTime = chien.vitesseAnimationTime = 0;
    chien.vitesse = 1000;

    chien.etat = CHIEN_MARCHE;
    chien.nbFrames = 5;
    chien.image[CHIEN_MARCHE].source = loadImageWithColorKey("sprites/chienMarche.png", 0, 255, 0);
    chien.image[CHIEN_MARCHE].lecture.h = 87;
    chien.image[CHIEN_MARCHE].lecture.w = 120;
    chien.image[CHIEN_MARCHE].lecture.x = 0;
    chien.image[CHIEN_MARCHE].lecture.y = 87;
    chien.image[CHIEN_MARCHE].position.x = 0;
    chien.image[CHIEN_MARCHE].position.y = Y_INTRO_CHIEN;

    chien.image[CHIEN_CONTENT].source = loadImageWithColorKey("sprites/chienContent.png", 0, 255, 0);
    chien.image[CHIEN_CONTENT].lecture.h = 100;
    chien.image[CHIEN_CONTENT].lecture.w = 113;
    chien.image[CHIEN_CONTENT].lecture.x = 0;
    chien.image[CHIEN_CONTENT].lecture.y = 96;

    chien.image[CHIEN_SAUTE_1].source = loadImageWithColorKey("sprites/chienSaute1.png", 0, 255, 0);
    chien.image[CHIEN_SAUTE_1].lecture.h = 100;
    chien.image[CHIEN_SAUTE_1].lecture.w = 94;
    chien.image[CHIEN_SAUTE_1].lecture.x = 0;
    chien.image[CHIEN_SAUTE_1].lecture.y = 0;

    chien.image[CHIEN_SAUTE_2].source = loadImageWithColorKey("sprites/chienSaute2.png", 0, 255, 0);
    chien.image[CHIEN_SAUTE_2].lecture.h = 100;
    chien.image[CHIEN_SAUTE_2].lecture.w = 94;
    chien.image[CHIEN_SAUTE_2].lecture.x = 0;
    chien.image[CHIEN_SAUTE_2].lecture.y = 0;

  /*  chien.image[CHIEN_RIGOLE].source = loadImageWithColorKey("sprites/chienMoqueur.png", 228, 255, 0);
    chien.image[CHIEN_CONTENT_SIMPLE].source = loadImageWithColorKey("sprites/chienContentSimple.png", 228, 255, 0);
    chien.image[CHIEN_CONTENT_DOUBLE].source = loadImageWithColorKey("sprites/chienContentDouble.png", 228, 255, 0);*/
}

void initCanard(Canard &cn)
{
    cn.etat = ALIVE; // On fait naître le canard.
    switch (cn.type)
    {
        case DARK:
            cn.image.source = loadImageWithColorKey("sprites/canardNoir.png", 228, 255, 0);
            cn.vitesse = VITESSE_N;
            break;
        case CHESNUT:
            cn.image.source = loadImageWithColorKey("sprites/canardRouge.png", 228, 255, 0);
            cn.vitesse = VITESSE_M;
            break;
        case BLUISH_PURPLE:
            cn.image.source = loadImageWithColorKey("sprites/canardViolet.png", 228, 255, 0);
            cn.vitesse = VITESSE_V;
            break;
    }
    cn.nbFrames = 3;
    cn.pxParFrame = 70;
    cn.cycleSprite = 0;
    cn.vitesseAnimation = 40; // Plus cette valeur est élevée, plus l'animation est lente...
    cn.vitesseTime = cn.vitesseAnimationTime = 0;

    cn.image.lecture.x = 0;
    cn.image.lecture.y = 0;
    cn.image.lecture.w = 70;
    cn.image.lecture.h = 70;
    cn.image.position.x = alea(1,LARGEUR-cn.image.lecture.w);
    cn.image.position.y = alea(1,HAUTEUR-LIMITE_BASSE - cn.image.lecture.h);
    do
    {
        cn.vecteurPositionX = alea(-10, 10);
        if(cn.vecteurPositionX >= 0)
        {
            cn.vecteurPositionY = 10 - cn.vecteurPositionX;
        }
        else
        {
            cn.vecteurPositionY = 10 + cn.vecteurPositionX;
        }
    } while(cn.vecteurPositionX == 0 || cn.vecteurPositionY == 0);

    cn.points.source = loadImageWithColorKey("sprites/points.png", 0, 0, 0);

    cn.points.lecture.h = 17;
    cn.points.lecture.w = 32;
}

