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

void genererRendu(Sprites sprites, SourisEvent sourisEvent, Partie partie)
{
    SDL_BlitSurface(sprites.background.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
    sprites.viseur.position.x = sourisEvent.sx - (sprites.viseur.source->w / 2);
    sprites.viseur.position.y = sourisEvent.sy - (sprites.viseur.source->h / 2);
    sprites.shots.lecture.x = 0 + partie.shots * 75;
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat == FREE_FALLING)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, SDL_GetVideoSurface(), &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.background_blit.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat != FREE_FALLING && sprites.canard[i].etat != DEAD)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, SDL_GetVideoSurface(), &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.shots.source, &sprites.shots.lecture, SDL_GetVideoSurface(), &sprites.shots.position);
    sprites.shots.lecture.y=0;
    sprites.hits.position.x=170;
    for (int i = 0; i < 10; i++)
    {
        sprites.hits.lecture.x = partie.hit[i] * 27;
        sprites.hits.position.x += sprites.hits.lecture.w + 3;
        SDL_BlitSurface(sprites.hits.source, &sprites.hits.lecture, SDL_GetVideoSurface(), &sprites.hits.position);
    }
    SDL_BlitSurface(sprites.viseur.source, NULL, SDL_GetVideoSurface(), &sprites.viseur.position);
}

void showPoints(Message &msg, TTF_Font *font, int points)
{
    static std::ostringstream message;
    message.flush();
    message.str("");
    message << points;
    msg.message = message.str();

    std::string mot="";
    std::string space=" ";
    int i = 0;
    size_t j;
    SDL_Surface *mes = NULL;

    j = msg.message.find(space);
    while( j != std::string::npos )
    {
        mot = msg.message.substr(i,j-i);
        if(mot != "")
        {
           mes = TTF_RenderText_Solid(font, mot.c_str(), msg.textColor);
           SDL_BlitSurface(mes, NULL, SDL_GetVideoSurface(),  &msg.position);
           msg.position.x += mes->w;
           SDL_FreeSurface(mes);
        }
        msg.position.x += msg.fontSize;
        i = j+1;
        j = msg.message.find(space,i);
    }

    mot = msg.message.substr(i);
    mes = TTF_RenderText_Solid(font, mot.c_str(), msg.textColor);
    SDL_BlitSurface(mes, NULL, SDL_GetVideoSurface(),  &msg.position);
    SDL_FreeSurface(mes);
}
