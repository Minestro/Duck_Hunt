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

void showMenu(Sprites sprites, Boutons boutons, int &modeMenu, Message msgs[], int sx, int sy)
{
    sprites.viseur.position.x=sx-(sprites.viseur.source->w/2);
    sprites.viseur.position.y=sy-(sprites.viseur.source->h/2);
    SDL_BlitSurface(sprites.background_menu.source, NULL, SDL_GetVideoSurface(), &sprites.background.position);
    switch (modeMenu)
    {
        case 1 :
            SDL_BlitSurface(boutons.source, &boutons.lecture[testHoverBouton(sx, sy, boutons.play, boutons.lecture[0])], SDL_GetVideoSurface(), &boutons.play.position);
            msgs[MSG_BOUTONS].source = TTF_RenderText_Solid(msgs[MSG_BOUTONS].font, boutons.play.contenu.c_str(), msgs[MSG_BOUTONS].textColor);
            msgs[MSG_BOUTONS].position.x=boutons.play.position.x+(boutons.lecture[0].w - msgs[MSG_BOUTONS].source->w)/2;
            msgs[MSG_BOUTONS].position.y=boutons.play.position.y+(boutons.lecture[0].h - msgs[MSG_BOUTONS].source->h)/2;
            SDL_BlitSurface(msgs[MSG_BOUTONS].source, NULL, SDL_GetVideoSurface(), &msgs[MSG_BOUTONS].position);
            SDL_BlitSurface(boutons.source, &boutons.lecture[testHoverBouton(sx, sy, boutons.quit, boutons.lecture[0])], SDL_GetVideoSurface(), &boutons.quit.position);
            msgs[MSG_BOUTONS].source = TTF_RenderText_Solid(msgs[MSG_BOUTONS].font, boutons.quit.contenu.c_str(), msgs[MSG_BOUTONS].textColor);
            msgs[MSG_BOUTONS].position.x=boutons.quit.position.x+(boutons.lecture[0].w - msgs[MSG_BOUTONS].source->w)/2;
            msgs[MSG_BOUTONS].position.y=boutons.quit.position.y+(boutons.lecture[0].h - msgs[MSG_BOUTONS].source->h)/2;
            SDL_BlitSurface(msgs[MSG_BOUTONS].source, NULL, SDL_GetVideoSurface(), &msgs[MSG_BOUTONS].position);
            SDL_FreeSurface(msgs[MSG_BOUTONS].source);
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

    SDL_BlitSurface(sprites.viseur.source, NULL, SDL_GetVideoSurface(), &sprites.viseur.position);
}

void showPointsCanard(Sprite &points, Canard canard)
{
    points.lecture.y = 32 * (canard.type - 1);
    points.position.x = canard.image.position.x + canard.image.lecture.w / 2;
    points.position.y = canard.image.position.y + canard.image.lecture.h / 2;
    SDL_BlitSurface(points.source, &points.lecture, SDL_GetVideoSurface(), &points.position);
}
