#include "main.h"

bool getEvents(SourisEvent &sourisEvent, bool testClic)
{
    int bl2, br2, bm2;
    if (testClic)
    {
        sourisEvent.bl2 = sourisEvent.bl;
        sourisEvent.br2 = sourisEvent.br;
        sourisEvent.bm2 = sourisEvent.bm;
    }
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

    if (testClic)
    {
        if((sourisEvent.bl!=sourisEvent.bl2)&&(sourisEvent.bl))
        {
            sourisEvent.clicGauche = true;
        }
        else
        {
            sourisEvent.clicGauche = false;
        }
        if((sourisEvent.br!=sourisEvent.br2)&&(sourisEvent.br))
        {
            sourisEvent.clicDroit = true;
        }
        else
        {
            sourisEvent.clicDroit = false;
        }
        if((sourisEvent.bm!=sourisEvent.bm2)&&(sourisEvent.bm))
        {
            sourisEvent.clicMolette = true;
        }
        else
        {
            sourisEvent.clicMolette = false;
        }
    }
    return event.type == SDL_QUIT;
}

