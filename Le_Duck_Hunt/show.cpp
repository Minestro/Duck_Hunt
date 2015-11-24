#include "main.h"

using namespace std;


void showMenu(SDL_Surface *ecran, Sprites sprites, Boutons boutons, int &modeMenu, int sx, int sy)
{
    SDL_ShowCursor(0);
    sprites.viseur.position.x=sx-(sprites.viseur.source->w/2);
    sprites.viseur.position.y=sy-(sprites.viseur.source->h/2);
    SDL_BlitSurface(sprites.background_menu.source, NULL, ecran, &sprites.background.position);
    switch (modeMenu)
    {
    case 1 :
        SDL_BlitSurface(boutons.source, &boutons.play.lecture[testHoverBouton(sx, sy, boutons.play)], ecran, &boutons.play.position);
        SDL_BlitSurface(boutons.source, &boutons.quit.lecture[testHoverBouton(sx, sy, boutons.quit)], ecran, &boutons.quit.position);
        break;
    }
    SDL_BlitSurface(sprites.viseur.source, NULL, ecran, &sprites.viseur.position);
    SDL_Flip(ecran);

}

void genererRendu(SDL_Surface *ecran, Sprites sprites, SourisEvent sourisEvent, int shots)
{
    SDL_ShowCursor(0);
    sprites.viseur.position.x=sourisEvent.sx-(sprites.viseur.source->w/2);    
    sprites.viseur.position.y=sourisEvent.sy-(sprites.viseur.source->h/2);
    SDL_BlitSurface(sprites.background.source, NULL, ecran, &sprites.background.position);
    for (int i=0; i<sprites.canardActifs; i++)
    {

        if (sprites.canard[i].etat == 1)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, ecran, &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.background_blit.source, NULL, ecran, &sprites.background.position);
    for (int i=0; i<sprites.canardActifs; i++)
    {

        if (sprites.canard[i].etat == 2)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, ecran, &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.viseur.source, NULL, ecran, &sprites.viseur.position);
    SDL_Flip(ecran);
}
