﻿#include "main.h"

void showBouton(SDL_Surface *ecran, Boutons &boutons, Message msgs[], int boutonNom, int sx, int sy)
{
    SDL_BlitSurface(boutons.source, &boutons.lecture[testHoverBouton(sx, sy, boutons.bouton[boutonNom], boutons.lecture[0])], ecran, &boutons.bouton[boutonNom].position);
    msgs[MSG_BOUTONS].source = TTF_RenderText_Solid(msgs[MSG_BOUTONS].font, boutons.bouton[boutonNom].contenu.c_str(), msgs[MSG_BOUTONS].textColor);
    msgs[MSG_BOUTONS].position.x=boutons.bouton[boutonNom].position.x+(boutons.lecture[0].w - msgs[MSG_BOUTONS].source->w)/2;
    msgs[MSG_BOUTONS].position.y=boutons.bouton[boutonNom].position.y+(boutons.lecture[0].h - msgs[MSG_BOUTONS].source->h)/2;
    SDL_BlitSurface(boutons.source, &boutons.lecture[testHoverBouton(sx, sy, boutons.bouton[boutonNom], boutons.lecture[0])], ecran, &boutons.bouton[boutonNom].position);
    SDL_BlitSurface(msgs[MSG_BOUTONS].source, NULL, ecran, &msgs[MSG_BOUTONS].position);
    SDL_FreeSurface(msgs[MSG_BOUTONS].source);
}

void showChien(SDL_Surface *ecran, Chien chien)
{
    SDL_BlitSurface(chien.image[chien.etat].source, &chien.image[chien.etat].lecture, ecran, &chien.image[chien.etat].position);
}

void showMenu(SDL_Surface *ecran, Sprites sprites, Boutons &boutons, int &modeMenu, Message msgs[], int sx, int sy)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 136, 255));
    sprites.viseur.position.x = sx - (sprites.viseur.source->w / 2);
    sprites.viseur.position.y = sy - (sprites.viseur.source->h / 2);
    SDL_BlitSurface(sprites.background_menu.source, NULL, ecran, &sprites.background.position);
    switch (modeMenu)
    {
    case 1 :
        showBouton(ecran, boutons, msgs, BOUTON_PLAY, sx, sy);
        showBouton(ecran, boutons, msgs, BOUTON_QUIT, sx, sy);
        break;
    case 5:
        SDL_BlitSurface(msgs[MSG_PAUSE].source, NULL, ecran, &msgs[MSG_PAUSE].position);

        showBouton(ecran, boutons, msgs, BOUTON_REPRENDRE, sx, sy);
        showBouton(ecran, boutons, msgs, BOUTON_QUIT, sx, sy);

        break;
    }
    SDL_BlitSurface(sprites.viseur.source, NULL, ecran, &sprites.viseur.position);
}

void genererRendu(SDL_Surface *ecran, Sprites sprites, SourisEvent sourisEvent, Partie partie, Chien chien, Message msgs[], DimensionsEcran dim)
{
    static SDL_Rect terre;
    terre.h = dim.hauteur -  sprites.background.position.y - sprites.background.source->h + 180;
    terre.w = dim.largeur;
    terre.x = 0;
    terre.y = sprites.background.position.y + sprites.background.source->h - 180;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 193, 255));
    SDL_FillRect(ecran, &terre, SDL_MapRGB(ecran->format, 142, 114, 0));
    SDL_BlitSurface(sprites.background.source, NULL, ecran, &sprites.background.position);
    sprites.viseur.position.x = sourisEvent.sx - (sprites.viseur.source->w / 2);
    sprites.viseur.position.y = sourisEvent.sy - (sprites.viseur.source->h / 2);
    sprites.shots.lecture.x = 0 + partie.shots * 75;
    sprites.shots.lecture.y = 0;
    if(!chien.devantHerbe)
    {
        showChien(ecran, chien);
    }
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (((sprites.canard[i].etat == FREE_FALLING) || ((sprites.canard[i].etat == ALIVE) && (sprites.canard[i].echappe))) && partie.jeu)
        {
            SDL_BlitSurface(sprites.canardSprite[sprites.canard[i].type - 1], &sprites.canard[i].lecture, ecran, &sprites.canard[i].position);
        }
    }
    SDL_BlitSurface(sprites.background_blit.source, NULL, ecran, &sprites.background.position);
    SDL_BlitSurface(sprites.extension.herbe.source, NULL, ecran, &sprites.extension.positions.aGauche);
    SDL_BlitSurface(sprites.extension.herbe.source, NULL, ecran, &sprites.extension.positions.aDroite);

    if(chien.devantHerbe)
    {
        showChien(ecran, chien);
    }
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if ((sprites.canard[i].etat == ALIVE || sprites.canard[i].etat == TOUCHED) && !sprites.canard[i].echappe && partie.jeu)
        {
            SDL_BlitSurface(sprites.canardSprite[sprites.canard[i].type - 1], &sprites.canard[i].lecture, ecran, &sprites.canard[i].position);
            if (sprites.canard[i].etat == TOUCHED)
            {
                showPointsCanard(ecran, sprites.canard[i], sprites.points);
            }
        }
    }

    SDL_BlitSurface(sprites.shots.source, &sprites.shots.lecture, ecran, &sprites.shots.position);
    for (int i = 0; i < 10; i++)
    {
        sprites.hits.lecture.x = partie.hit[i] * 27;
        sprites.hits.position.x += sprites.hits.lecture.w + 3;
        SDL_BlitSurface(sprites.hits.source, &sprites.hits.lecture, ecran, &sprites.hits.position);
    }

    if(partie.afficherMsgTransition)
    {
    //    showMessage(...);
    }

    showPoints(msgs, ecran, partie);

    SDL_BlitSurface(sprites.viseur.source, NULL, ecran, &sprites.viseur.position);
}

void showPointsCanard(SDL_Surface *ecran, Canard canard, Sprite &points)
{
    points.position.x = canard.position.x + canard.lecture.w / 2;
    points.position.y = canard.position.y + canard.lecture.h;
    points.lecture.y = 17 * (canard.type - 1);
    SDL_BlitSurface(points.source, &points.lecture, ecran, &points.position);
}

void showPoints(Message msgs[], SDL_Surface *ecran, Partie partie)
{
    msgs[MSG_SCORE].source = TTF_RenderText_Solid(msgs[MSG_SCORE].font, intToString(partie.score).c_str(), msgs[MSG_SCORE].textColor);
    SDL_BlitSurface(msgs[MSG_SCORE].source, NULL, ecran, &msgs[MSG_SCORE].position);
    SDL_FreeSurface(msgs[MSG_SCORE].source);
}


void showMessage(SDL_Surface *ecran, Message &msg)
{
    std::ostringstream message;
    message.flush();
    message.str("");
    message << msg.message;
    msg.message = message.str();

    std::string mot="";
    std::string space=" ";
    int i = 0;
    size_t j;
    SDL_Surface *mes = NULL;

    j = msg.message.find(space);
    while(j != std::string::npos)
    {
        mot = msg.message.substr(i,j-i);
        if(mot != "")
        {
           mes = TTF_RenderText_Solid(msg.font, mot.c_str(), msg.textColor);
           SDL_BlitSurface(mes, NULL, ecran,  &msg.position);
           msg.position.x += mes->w;
           SDL_FreeSurface(mes);
        }
        msg.position.x += msg.fontSize;
        i = j+1;
        j = msg.message.find(space,i);
    }
    mot = msg.message.substr(i);
    mes = TTF_RenderText_Solid(msg.font, mot.c_str(), msg.textColor);
    SDL_BlitSurface(mes, NULL, ecran,  &msg.position);
    SDL_FreeSurface(mes);
}

std::string intToString (int number)
{
    std::ostringstream oss;
    oss.flush();
    oss.str("");
    oss << number;
    return oss.str();
}
