// coucou
#define AHA
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include "header.h"

using namespace std;

void showMenu(int &modeMenu, int &modeJeu)
{

}

bool testHover(int sx, int sy, Sprite bouton)
{
    return((sx < bouton.position.x+bouton.lecture.w)&&(sx > bouton.position.x)&&(sy > bouton.position.y)&&(sy < bouton.position.y+bouton.lecture.h));
}
