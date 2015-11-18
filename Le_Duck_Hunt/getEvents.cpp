#include "main.h"

bool getEvents(SourisEvent &sourisEvent, Uint8 *keystates, Time &time)
{
    bool sdlQuit = false;
    time.currentTime = SDL_GetTicks();
    if (time.currentTime>=time.timeEvents+time.eventsTime)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
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
                    sourisEvent.bl = true;
                    break;
                case SDL_BUTTON_RIGHT :
                    sourisEvent.br = true;
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
                case SDL_BUTTON_MIDDLE :
                    sourisEvent.bm = false;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        keystates = SDL_GetKeyState(NULL);
        time.eventsTime = time.currentTime;
    }
    return sdlQuit;
}
