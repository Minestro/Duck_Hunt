#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include "main.h"

using namespace std;

void afficherImage(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,&ecran->clip_rect, SDL_MapRGB(ecran->format,0,0,0));
    SDL_Flip(ecran);
}
