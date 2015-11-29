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

void genererRendu(Sprites sprites, SourisEvent sourisEvent, int shots)
{
    sprites.viseur.position.x = sourisEvent.sx - (sprites.viseur.source->w / 2);
    sprites.viseur.position.y = sourisEvent.sy - (sprites.viseur.source->h / 2);
    sprites.shots.lecture.x = 0 + shots * 75;
    SDL_BlitSurface(sprites.background.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
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
        if (sprites.canard[i].etat != FREE_FALLING)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, SDL_GetVideoSurface(), &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.shots.source, &sprites.shots.lecture, SDL_GetVideoSurface(), &sprites.shots.position);
    SDL_BlitSurface(sprites.viseur.source, NULL, SDL_GetVideoSurface(), &sprites.viseur.position);
    SDL_Flip(SDL_GetVideoSurface());
}

void showMessageScreen(std::string message, SDL_Rect position,
          TTF_Font *font,int fontSize,SDL_Color textColor)
{
  std::string mot="";
  std::string space=" ";
  size_t j;
  int i = 0;
  SDL_Surface *mes=NULL;
  int x = position.x;
  j = message.find(space);
  while( j != std::string::npos )
  {
      mot=message.substr(i,j-i);
      if(mot != "")
      {
         mes=TTF_RenderText_Solid(font,mot.c_str(),textColor);
         SDL_BlitSurface(mes, NULL, SDL_GetVideoSurface(), &position);
         x+=mes->w;
         SDL_FreeSurface(mes);
      }
      x+=fontSize;
      i=j+1;
      j = message.find(space,i);
  }

  mot=message.substr(i);
  mes=TTF_RenderText_Solid(font,mot.c_str(),textColor);
  SDL_BlitSurface(mes, NULL, SDL_GetVideoSurface(), &position);
  SDL_FreeSurface(mes);
}
