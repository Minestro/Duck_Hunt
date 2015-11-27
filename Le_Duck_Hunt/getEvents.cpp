#include "main.h"

bool getEvents(SourisEvent &sourisEvent)
{
    int bl2, br2, bm2;
    bl2 = sourisEvent.bl;
    br2 = sourisEvent.br;
    bm2 = sourisEvent.bm;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            sourisEvent.sx = event.motion.x;
            sourisEvent.sy = event.motion.y;
        case SDL_MOUSEBUTTONDOWN :
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT :
                sourisEvent.bl = true;
                break;
            case SDL_BUTTON_RIGHT :
                sourisEvent.br = true;
                break;
            case SDL_BUTTON_MIDDLE :
                sourisEvent.bm = true;
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP :
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT :
                sourisEvent.bl = false;
                break;
            case SDL_BUTTON_RIGHT :
                sourisEvent.br = false;
                break;
            case SDL_BUTTON_MIDDLE :
                sourisEvent.bm = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    if((sourisEvent.bl!=bl2)&&(sourisEvent.bl))
    {
        sourisEvent.clicGauche = true;
    }
    if((sourisEvent.br!=br2)&&(sourisEvent.br))
    {
        sourisEvent.clicDroit = true;
    }
    if((sourisEvent.bm!=bm2)&&(sourisEvent.bm))
    {
        sourisEvent.clicMolette = true;
    }

    return event.type == SDL_QUIT;
}

