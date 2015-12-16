#include "main.h"

void initTableau(TableauChasse &tableau, Sprites sprites)
{
    for(int i = 0 ; i < sprites.canardActifs ; i++)
    {
        tableau.typeCanard[i] = NOT_SET;
    }
}

void initFichiers()
{
    std::fstream f1, f2;
    f1.open("scoresClassic", std::ios::in);
    if (f1.fail())
    {
        f2.open("scoresClassic", std::ios::out);
        for (int i=0; i<NB_HIGH_SCORE; i++)
        {
            f2 << "Not_Set";
            f2 << " ";
            f2 << 0;
            f2 << " ";
        }
        f2.close();
    }
    f1.close();
    f1.open("scoresAvancee", std::ios::in);
    if (f1.fail())
    {
        f2.open("scoresAvancee", std::ios::out);
        for (int i=0; i<NB_HIGH_SCORE; i++)
        {
            f2 << "Not_Set";
            f2 << " ";
            f2 << 0;
            f2 << " ";
        }
        f2.close();
    }
    f1.close();
}

void initMessage(Message msgs[])
{
    msgs[MSG_SCORE].position.x = 580;
    msgs[MSG_SCORE].position.y = 667;
    msgs[MSG_PAUSE].position.y = 100;
    msgs[MSG_NIVEAU].position.y = HAUTEUR/2;
    msgs[MSG_0_TOUCHE].position.x = LARGEUR / 2;
    msgs[MSG_0_TOUCHE].position.y = 20;

    msgs[MSG_SCORE].fontSize = 35;
    msgs[MSG_BOUTONS].fontSize = 40;
    msgs[MSG_PAUSE].fontSize = 40;
    msgs[MSG_NIVEAU].fontSize = 70;
    msgs[MSG_TEXTE].fontSize = 35;
    msgs[MSG_SCORE_ROUGE].fontSize = 60;
    msgs[MSG_TABLEAU_SCORE].fontSize = 50;
    msgs[MSG_PSEUDO].fontSize = 50;
    msgs[MSG_0_TOUCHE].fontSize = 50;

    for (int i = 0 ; i < NOMBRE_MESSAGES; i++)
    {
        msgs[i].textColor.r = 255;
        msgs[i].textColor.g = 255;
        msgs[i].textColor.b = 255;
        msgs[i].font = TTF_OpenFont("font/duck_hunt.ttf", msgs[MSG_SCORE].fontSize);
    }
    msgs[MSG_SCORE_ROUGE].textColor = {255,0,0};

    msgs[MSG_0_TOUCHE].message = "AUCUN_CANARD_MORT";
    msgs[MSG_PAUSE].message = "Jeu en pause";
}

void initBouton(Boutons &boutons)
{
    boutons.source = loadImageWithColorKey("sprites/boutons.bmp", 0, 0, 0);
    boutons.bouton[BOUTON_PLAY].contenu = "Jouer";
    boutons.bouton[BOUTON_QUIT].contenu = "Quitter";
    boutons.bouton[BOUTON_REPRENDRE].contenu = "Reprendre";
    boutons.bouton[BOUTON_RETOUR].contenu = "Retour";
    boutons.bouton[BOUTON_SCORE].contenu = "High Score";
    boutons.bouton[BOUTON_OK].contenu = "OK";
    for(int i = 0 ; i < 2 ; i++)
    {
        boutons.lecture[i].x = i * 226;
        boutons.lecture[i].y = 0;
        boutons.lecture[i].w = 216;
        boutons.lecture[i].h = 74;
    }
}

void initSourisEvent(SourisEvent &sourisEvent)
{
    sourisEvent.bl = sourisEvent.bm = sourisEvent.br = sourisEvent.bl2 = sourisEvent.bm2 = sourisEvent.br2 = false;
    sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
}

void initTime(Time &time)
{
    time.fpsTime = (1 / (FPS_MAX * 1.0) * 1000); // Calcule en ms le temps entre chaque actualisation d'image à partir de la constante FPS_LIMIT.
    time.timeFps = 0;
    time.menuTime = 2000;       //temps d'affichage du niveau par exemple.
    time.timeMenu = 0;
    time.keyTime = 700;
    time.timeKey = 0;
    time.defKeyTime = 100;
    time.timeDefKey = 0;
    time.currentTime = SDL_GetTicks();
}

void initPartie(Partie &partie, int nbCanards)
{
    partie.round = 0;
    partie.jeu = false;
    partie.relancer = false;
    partie.chienEnChasse = false;
    for(int i = 0 ; i < nbCanards ; i++)
    {
        partie.canardRamasse[i] = false;
        partie.xChute[i] = NOT_SET;
    }
    partie.canardAbbatu = false;
    partie.shots = 3;
    partie.canardsEnVie = nbCanards;
    partie.alreadyShot = false;
    partie.alreadyGetEvent = false;
    partie.alreadyClic = false;
    for (int i = 0;  i < 10; i++)
    {
        partie.hit[i] = HIT_EMPTY;
    }
}

void initChien(Chien &chien)
{
    chien.devantHerbe = true;
    chien.vecteurPositionX = 10;
    chien.vecteurPositionY = 0;
    chien.cycleSprite = 0;
    chien.vitesseAnimation = 100; // Plus cette valeur est élevée, plus l'animation est lente...
    chien.vitesseAnimationTime = 0;

    chien.etat = CHIEN_MARCHE;
    chien.nbFrames = 5;
    chien.image[CHIEN_MARCHE].position.x = 0;
    chien.image[CHIEN_MARCHE].position.y = Y_INTRO_CHIEN;

    chien.image[CHIEN_MARCHE].lecture.x = 0;
    chien.image[CHIEN_MARCHE].lecture.y = 87;

    chien.image[CHIEN_CONTENT].lecture.x = 0;
    chien.image[CHIEN_CONTENT].lecture.y = 96;

    chien.image[CHIEN_SAUTE_1].lecture.x = 0;
    chien.image[CHIEN_SAUTE_1].lecture.y = 0;

    chien.image[CHIEN_SAUTE_2].lecture.x = 0;
    chien.image[CHIEN_SAUTE_2].lecture.y = 0;

    chien.image[CHIEN_RIGOLE].lecture.x = 0;
    chien.image[CHIEN_RIGOLE].lecture.y = 0;

    chien.image[CHIEN_CONTENT_SIMPLE].lecture.x = 0;
    chien.image[CHIEN_CONTENT_SIMPLE].lecture.y = 0;

    chien.image[CHIEN_CONTENT_DOUBLE].lecture.x = 0;
    chien.image[CHIEN_CONTENT_DOUBLE].lecture.y = 0;
}

void initCanard(Canard &cn, Partie partie)
{
    cn.etat = ALIVE; // On fait naître le canard.
    cn.echappe = false;
    switch (cn.type)
    {
        case DARK:
            cn.vitesse = VITESSE_N-((partie.niveau-1)*2);
            break;
        case CHESNUT:
            cn.vitesse = VITESSE_M-((partie.niveau-1)*2);
            break;
        case BLOOD:
            cn.vitesse = VITESSE_B-((partie.niveau-1)*2);
            break;
        case BLUISH_PURPLE:
            cn.vitesse = VITESSE_V-((partie.niveau-1)*2);
            break;
    }
    if (cn.vitesse<0)
    {
        cn.vitesse = 0;
    }
    cn.nbFrames = 3;
    cn.cycleSprite = 0;
    cn.vitesseAnimation = 40; // Plus cette valeur est élevée, plus l'animation est lente...
    cn.vitesseTime = cn.vitesseAnimationTime = 0;

    cn.lecture.x = 0;
    cn.lecture.y = 0;
    cn.lecture.w = 70;
    cn.lecture.h = 70;
    cn.position.x = alea(1, LARGEUR-cn.lecture.w);
    cn.position.y = alea(1, HAUTEUR-LIMITE_BASSE - cn.lecture.h);
    do
    {
        cn.vecteurPositionX = alea(-10, 10);
        if(cn.vecteurPositionX >= 0)
        {
            cn.vecteurPositionY = 10 - cn.vecteurPositionX;
        }
        else
        {
            cn.vecteurPositionY = 10 + cn.vecteurPositionX;
        }

    } while(cn.vecteurPositionX == 0 || cn.vecteurPositionY == 0);
}

void initHighScore(HighScore highScore[])
{
    for (int i=0; i<NB_HIGH_SCORE; i++)
    {
        highScore[i].nom = "";
        highScore[i].score = 0;
    }
}
