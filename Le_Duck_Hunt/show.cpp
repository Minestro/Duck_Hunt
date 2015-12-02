#include "main.h"

void showMenu(Sprites sprites, Boutons boutons, int &modeMenu, int sx, int sy)
{
    sprites.viseur.position.x=sx-(sprites.viseur.source->w/2);
    sprites.viseur.position.y=sy-(sprites.viseur.source->h/2);
    SDL_BlitSurface(sprites.background_menu.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
    switch (modeMenu)
    {
    case 1 :
        SDL_BlitSurface(boutons.source, &boutons.play.lecture[testHoverBouton(sx, sy, boutons.play)], SDL_GetVideoSurface(), &boutons.play.position);
        SDL_BlitSurface(boutons.source, &boutons.quit.lecture[testHoverBouton(sx, sy, boutons.quit)], SDL_GetVideoSurface(), &boutons.quit.position);
        break;
    }
    SDL_BlitSurface(sprites.viseur.source, NULL, SDL_GetVideoSurface(), &sprites.viseur.position);
    SDL_Flip(SDL_GetVideoSurface());
}

void genererRendu(Sprites sprites, SourisEvent sourisEvent, Partie partie, SDL_Surface *screen)
{
    SDL_BlitSurface(sprites.background.source, NULL, screen, &sprites.background.position);
    sprites.viseur.position.x = sourisEvent.sx - (sprites.viseur.source->w / 2);
    sprites.viseur.position.y = sourisEvent.sy - (sprites.viseur.source->h / 2);
    sprites.shots.lecture.x = 0 + partie.shots * 75;
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat == FREE_FALLING)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, screen, &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.background_blit.source, NULL, screen, &sprites.background.position);
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat != FREE_FALLING && sprites.canard[i].etat != DEAD)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, screen, &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.shots.source, &sprites.shots.lecture, screen, &sprites.shots.position);
    sprites.shots.lecture.y=0;
    sprites.hits.position.x=170;
    for (int i = 0; i < 10; i++)
    {
        sprites.hits.lecture.x = partie.hit[i] * 27;
        sprites.hits.position.x += sprites.hits.lecture.w + 3;
        SDL_BlitSurface(sprites.hits.source, &sprites.hits.lecture, screen, &sprites.hits.position);
    }
    SDL_BlitSurface(sprites.viseur.source, NULL, screen, &sprites.viseur.position);

    SDL_Flip(screen);
}

void showMsg(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface( source, clip, destination, &position );
}

void showMessageScreen(std::string message,int x,int y, TTF_Font *font,int fontSize,SDL_Color textColor,SDL_Surface* &screen)
{
    std::string mot="";
    std::string space=" ";
    int i=0,j;
    SDL_Surface *mes=NULL;

    j = message.find(space);
    while( j != std::string::npos )
    {
        mot=message.substr(i,j-i);
        if(mot != "")
        {
            mes=TTF_RenderText_Solid(font,mot.c_str(),textColor);
            showMsg(x,y,mes,screen,NULL);
            x+=mes->w;
            SDL_FreeSurface(mes);
        }
        x+=fontSize;
        i=j+1;
        j = message.find(space,i);
    }

    mot=message.substr(i);
    mes=TTF_RenderText_Solid(font,mot.c_str(),textColor);
    showMsg(x,y,mes,screen,NULL);
    SDL_FreeSurface(mes);
}
