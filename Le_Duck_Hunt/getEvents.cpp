#include "main.h"

bool getEvents(SourisEvent &sourisEvent)
{
    bool sdlQuit = false;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
        switch (event.type)
        {
        case SDL_QUIT:
            sdlQuit = true;
            break;
        case SDL_MOUSEMOTION:
            sourisEvent.sx = event.motion.x;
            sourisEvent.sy = event.motion.y;
        case SDL_MOUSEBUTTONDOWN :
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT :
                if (SDL_BUTTON_LEFT != sourisEvent.bl)
                {
                    sourisEvent.clicGauche = true;
                }
                sourisEvent.bl = true;
                break;
            case SDL_BUTTON_RIGHT :
                if (SDL_BUTTON_RIGHT != sourisEvent.br)
                {
                    sourisEvent.clicDroit = true;
                }
                sourisEvent.br = true;
            case SDL_BUTTON_MIDDLE :
                if (SDL_BUTTON_RIGHT != sourisEvent.bm)
                {
                    sourisEvent.clicMolette = true;
                }
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
                if (SDL_BUTTON_LEFT != sourisEvent.bl)
                {
                    sourisEvent.clicGauche = true;
                }
                sourisEvent.bl = false;
                break;
            case SDL_BUTTON_RIGHT :
                if (SDL_BUTTON_RIGHT != sourisEvent.br)
                {
                    sourisEvent.clicDroit = true;
                }
                sourisEvent.br = false;
            case SDL_BUTTON_MIDDLE :
                if (SDL_BUTTON_RIGHT != sourisEvent.bm)
                {
                    sourisEvent.clicMolette = true;
                }
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
    return sdlQuit;
}
