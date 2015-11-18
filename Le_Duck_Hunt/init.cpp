#include "main.h"

void initBouton(Bouton &bouton, int ligne)
{
    ligne = ligne * 100;
    bouton.lecture[0].x=0;
    bouton.lecture[0].y=ligne;
    bouton.lecture[0].w=150;
    bouton.lecture[0].h=60;

    bouton.lecture[1].x=200;
    bouton.lecture[1].y=ligne;
    bouton.lecture[1].w=150;
    bouton.lecture[1].h=60;

}

void initSourisEvent(SourisEvent &sourisEvent)
{
    sourisEvent.bl = sourisEvent.bm = sourisEvent.br = 0;
}

void initTime(Time &time)
{
    time.fpsTime = (1/(FPS_MAX*1.0)*1000); // Calcule en ms le temps entre chaque actualisation d'image à partir de la constante FPS_LIMIT.
    time.eventsTime = 10;
    time.vitesseCanard = 16;
}

void initCanard(Canard &cn)
{
    cn.image.source = loadImageWithColorKey("sprites/canardNoir.png", 228, 255, 0);
    cn.image.lecture.x = 0;
    cn.image.lecture.y = 0;
    cn.image.lecture.w = 70;
    cn.image.lecture.h = 70;
    cn.image.position.x = SDL_GetTicks() * SDL_GetTicks() % (LARGEUR - cn.image.lecture.w);
    cn.image.position.y = SDL_GetTicks() * SDL_GetTicks() % (HAUTEUR - cn.image.lecture.h - 360);
    cn.cycleSprite = 0;

    cn.vecteurPositionX = SDL_GetTicks() % 10 - 5;
    if(cn.vecteurPositionX >= 0)
    {
        cn.vecteurPositionY = 5 - cn.vecteurPositionX;
    }
    else
    {
        cn.vecteurPositionY = 5 + cn.vecteurPositionX;
    }
}
