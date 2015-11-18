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
    time.fpsTime = (1/(FPS_MAX*1.0)*1000);    //Calcule en ms le temps entre chaque actualisation d'image à partir de la constante FPS_LIMIT.
    time.eventsTime = 999;
    time.currentTime = time.timeRefresh = time.timeEvents = 0;
}
