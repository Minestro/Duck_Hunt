#include "main.h"

void menu(SDL_Surface *ecran, Sprites &sprites, Boutons &boutons, int &modeMenu, int &modeJeu, SourisEvent &sourisEvent, Time &time, Message msgs[], Partie &partie, Chien &chien)
{
    bool sortir = false;
    int lastKeyPressed;
    int lastKeyPressedBis;
    bool keyPressed = false;
    bool keyPressedBis = false;
    bool defilTouche = false;
    for (int i=0; i<LONGUEUR_MAX_PSEUDO; i++)
    {
        partie.pseudoT[i] = 0;
    }
    getScore("scoresClassic", partie.highScore);
    int carActif = 0;
    Uint8 *keystate = SDL_GetKeyState(NULL);
    time.currentTime = SDL_GetTicks();
    time.timeMenu = time.currentTime;
    time.timeKey = time.currentTime;
    time.timeDefKey = time.currentTime;
    partie.score = -99;
    while (!sortir && modeMenu!=0)
    {
        if (getEvents(sourisEvent, 1))
        {
            modeMenu = 0;
            modeJeu = 0;
        }
        time.currentTime = SDL_GetTicks();
        switch (modeMenu)
        {
        case 0:
            sortir = true;
            break;
        case 1 :
            boutons.bouton[BOUTON_PLAY].position.x = (LARGEUR - boutons.lecture[0].w) / 2;
            boutons.bouton[BOUTON_PLAY].position.y = 150;

            boutons.bouton[BOUTON_SCORE].position.x = (LARGEUR - boutons.lecture[0].w) / 2;
            boutons.bouton[BOUTON_SCORE].position.y = 300;

            boutons.bouton[BOUTON_QUIT].position.x = (LARGEUR - boutons.lecture[0].w) / 2;
            boutons.bouton[BOUTON_QUIT].position.y = 450;

            if (time.currentTime >= time.timeFps + time.fpsTime)
            {
                showMenu(ecran, sprites, boutons, modeMenu, msgs, partie, sourisEvent.sx, sourisEvent.sy);
                time.timeFps = time.currentTime;
            }

            if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_QUIT], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 0;
                modeJeu = 0;
            }
            else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_PLAY], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeJeu = 1;
                modeMenu = 6;
                initChien(chien);

                sprites.canardActifs = 2;

                for (int i = 0 ; i < sprites.canardActifs ; i++)
                {
                    sprites.canard[i].type = alea(0, 3);
                    initCanard(sprites.canard[i], partie);
                }
                partie.niveau = 0;
                initPartie(partie, sprites.canardActifs);
                initTableau(partie.tableauChasse, sprites);
            }
            else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_SCORE], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 7;
            }
            break;
        case 5 :
            boutons.bouton[BOUTON_REPRENDRE].position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_REPRENDRE].position.y = 200;

            boutons.bouton[BOUTON_QUIT].position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_QUIT].position.y = 400;

            if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_QUIT], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 1;
            }
            else if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_REPRENDRE], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 0;
            }

            if (time.currentTime >= time.timeFps + time.fpsTime)
            {
                showMenu(ecran, sprites, boutons, modeMenu, msgs, partie, sourisEvent.sx, sourisEvent.sy);
                time.timeFps = time.currentTime;
            }
            break;
        case 6:
            if (time.currentTime >= time.menuTime + time.timeMenu)
            {
                modeMenu = 0;
                time.timeMenu = time.currentTime;
            }
            else
            {
                if (time.currentTime >= time.timeFps + time.fpsTime)
                {
                    showMenu(ecran, sprites, boutons, modeMenu, msgs, partie, sourisEvent.sx, sourisEvent.sy);
                    time.timeFps = time.currentTime;
                }
            }
            break;
        case 7:
            boutons.bouton[BOUTON_RETOUR].position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_RETOUR].position.y = 600;

            if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_RETOUR], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                modeMenu = 1;
            }
            if (time.currentTime >= time.timeFps + time.fpsTime)
            {
                showMenu(ecran, sprites, boutons, modeMenu, msgs, partie, sourisEvent.sx, sourisEvent.sy);
                time.timeFps = time.currentTime;
            }
            break;
        case 8:
            boutons.bouton[BOUTON_OK].position.x = (LARGEUR/2) - (boutons.lecture[0].w/2);
            boutons.bouton[BOUTON_OK].position.y = 600;

            lastKeyPressedBis = lastKeyPressed;
            keyPressedBis = keyPressed;
            keyPressed = false;
            if (carActif < LONGUEUR_MAX_PSEUDO-1)
            {
                for (int i=97; i<123; i++)
                {
                    if (keystate[i])
                    {
                        lastKeyPressed = i;
                        keyPressed = true;
                    }
                }
            }
            if ((carActif > 0)&&keystate[SDLK_BACKSPACE])
            {
                lastKeyPressed = -1;
                keyPressed = true;
            }
            if ((lastKeyPressedBis !=lastKeyPressed)||(defilTouche&&(time.currentTime >= time.timeDefKey + time.defKeyTime))||(keyPressedBis!=keyPressed))
            {
                if (keyPressedBis!=keyPressed)
                {
                    defilTouche = false;
                }
                if (carActif < LONGUEUR_MAX_PSEUDO-1)
                {
                    for (int i=97; i<123; i++)
                    {
                        if (keystate[i])
                        {
                            partie.pseudoT[carActif]=(i-32);
                            carActif++;
                            time.timeKey = time.currentTime;
                        }
                    }
                }
                if ((carActif > 0)&&keystate[SDLK_BACKSPACE])
                {
                    partie.pseudoT[carActif-1]=0;
                    carActif--;
                    time.timeKey = time.currentTime;
                }
                if (defilTouche)
                {
                    time.timeDefKey = time.currentTime;
                }
            }
            else
            {
                if ((time.currentTime >= time.timeKey + time.keyTime)&&keyPressed)
                {
                    defilTouche = true;
                }
            }

            partie.pseudo = std::string(partie.pseudoT);
            if (time.currentTime >= time.timeFps + time.fpsTime)
            {
                showMenu(ecran, sprites, boutons, modeMenu, msgs, partie, sourisEvent.sx, sourisEvent.sy);
                time.timeFps = time.currentTime;
            }
            if ((testHoverBouton(sourisEvent.sx, sourisEvent.sy, boutons.bouton[BOUTON_OK], boutons.lecture[0]))&&sourisEvent.clicGauche)
            {
                addScore("scoresClassic", partie.pseudo, partie.score, partie.highScore);
                modeMenu = 1;
            }
            break;
        default:
            break;
        }
        SDL_Flip(ecran);
    }
}

bool testHoverBouton(int sx, int sy, Bouton sprite, SDL_Rect lecture)
{
    return((sx < sprite.position.x+lecture.w)&&(sx > sprite.position.x)&&(sy > sprite.position.y)&&(sy < sprite.position.y+lecture.h));
}
