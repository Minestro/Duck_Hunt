﻿#include "main.h"

void showMenu(SDL_Surface *ecran, Sprites sprites, Boutons boutons, int &modeMenu, int sx, int sy)
{
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
    sprites.viseur.position.x = sourisEvent.sx - (sprites.viseur.source->w / 2);
    sprites.viseur.position.y = sourisEvent.sy - (sprites.viseur.source->h / 2);
    sprites.shots.lecture.x = 0 + shots * 75;
    SDL_BlitSurface(sprites.background.source, NULL, ecran, &sprites.background.position);
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat == FREE_FALLING)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, ecran, &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.background_blit.source, NULL, ecran, &sprites.background.position);
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat != FREE_FALLING)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, ecran, &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.shots.source, &sprites.shots.lecture, ecran, &sprites.shots.position);
    SDL_BlitSurface(sprites.viseur.source, NULL, ecran, &sprites.viseur.position);
    SDL_Flip(ecran);
}

void showMessageScreen(std::string message, SDL_Rect position,
          TTF_Font *font,int fontSize,SDL_Color textColor,SDL_Surface* &screen)
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
         SDL_BlitSurface(mes, NULL, screen, &position);
         x+=mes->w;
         SDL_FreeSurface(mes);
      }
      x+=fontSize;
      i=j+1;
      j = message.find(space,i);
  }

  mot=message.substr(i);
  mes=TTF_RenderText_Solid(font,mot.c_str(),textColor);
  SDL_BlitSurface(mes, NULL, screen, &position);
  SDL_FreeSurface(mes);
}
