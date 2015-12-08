#include "main.h"

void afficherChien(Chien chien)
{
    SDL_BlitSurface(chien.image[chien.etat].source, &chien.image[chien.etat].lecture, SDL_GetVideoSurface(), &chien.image[chien.etat].position);
}

std::string intToString (int number)
{
    std::ostringstream oss;
    oss<< number;
    return oss.str();
}

void showMenu(Sprites sprites, Boutons boutons, int &modeMenu, Message message, int sx, int sy)
{
    sprites.viseur.position.x=sx-(sprites.viseur.source->w/2);
    sprites.viseur.position.y=sy-(sprites.viseur.source->h/2);
    SDL_BlitSurface(sprites.background_menu.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
    switch (modeMenu)
    {
        case 1 :
            SDL_BlitSurface(boutons.source, &boutons.lecture[testHoverBouton(sx, sy, boutons.play, boutons.lecture[0])], SDL_GetVideoSurface(), &boutons.play.position);
            message.position.x=boutons.play.position.x;
            showMessage(message, boutons.play.contenu);
            SDL_BlitSurface(boutons.source, &boutons.lecture[testHoverBouton(sx, sy, boutons.quit, boutons.lecture[0])], SDL_GetVideoSurface(), &boutons.quit.position);
            break;
    }

    SDL_BlitSurface(sprites.viseur.source, NULL, SDL_GetVideoSurface(), &sprites.viseur.position);
}

void genererRendu(Sprites sprites, SourisEvent sourisEvent, Partie partie, Chien chien)
{
    SDL_BlitSurface(sprites.background.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
    sprites.viseur.position.x = sourisEvent.sx - (sprites.viseur.source->w / 2);
    sprites.viseur.position.y = sourisEvent.sy - (sprites.viseur.source->h / 2);
    sprites.shots.lecture.x = 0 + partie.shots * 75;
    if(!chien.devantHerbe)
    {
        afficherChien(chien);
    }
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat == FREE_FALLING)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, SDL_GetVideoSurface(), &sprites.canard[i].image.position);
        }
    }
    SDL_BlitSurface(sprites.background_blit.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
    if(chien.devantHerbe)
    {
        afficherChien(chien);
    }
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat != FREE_FALLING && sprites.canard[i].etat != DEAD)
        {
            SDL_BlitSurface(sprites.canard[i].image.source, &sprites.canard[i].image.lecture, SDL_GetVideoSurface(), &sprites.canard[i].image.position);
        }
    }
    for (int i = 0 ; i < sprites.canardActifs ; i++)
    {
        if (sprites.canard[i].etat == TOUCHED)
        {
            showPointsCanard(sprites.points, sprites.canard[i]);
        }
    }
    SDL_BlitSurface(sprites.shots.source, &sprites.shots.lecture, SDL_GetVideoSurface(), &sprites.shots.position);
    sprites.shots.lecture.y = 0;
    sprites.hits.position.x = 170;
    for (int i = 0; i < 10; i++)
    {
        sprites.hits.lecture.x = partie.hit[i] * 27;
        sprites.hits.position.x += sprites.hits.lecture.w + 3;
        SDL_BlitSurface(sprites.hits.source, &sprites.hits.lecture, SDL_GetVideoSurface(), &sprites.hits.position);
    }

    SDL_BlitSurface(sprites.points.source, NULL, SDL_GetVideoSurface(), &sprites.points.position);
    SDL_BlitSurface(sprites.viseur.source, NULL, SDL_GetVideoSurface(), &sprites.viseur.position);
}

void showPointsCanard(Sprite &points, Canard canard)
{
    points.lecture.y = 32 * canard.type;
    points.position.x = canard.image.position.x + canard.image.lecture.w / 2;
    points.position.y = canard.image.position.y + canard.image.lecture.h / 2;
    SDL_BlitSurface(points.source, &points.position, SDL_GetVideoSurface(), &points.lecture);
}


void showMessage(Message &msg, std::string contenuMessage)
{
    static std::ostringstream message;
    message.flush();
    message.str("");
    message << contenuMessage;
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
           SDL_BlitSurface(mes, NULL, SDL_GetVideoSurface(),  &msg.position);
           msg.position.x += mes->w;
           SDL_FreeSurface(mes);
        }
        msg.position.x += msg.fontSize;
        i = j+1;
        j = msg.message.find(space,i);
    }
    mot = msg.message.substr(i);
    mes = TTF_RenderText_Solid(msg.font, mot.c_str(), msg.textColor);
    SDL_BlitSurface(mes, NULL, SDL_GetVideoSurface(),  &msg.position);
    SDL_FreeSurface(mes);
}
