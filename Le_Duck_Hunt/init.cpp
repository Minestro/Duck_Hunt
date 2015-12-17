#include "init.h"
#include "alea.h"

/****************** Nom de la fonction ****************************
* initTableau                                                     *
******************** Auteur , Dates *******************************
* Nom : LE HO                                                     *
********************* Description *********************************
* Affecte à chaque case du tableau de chasse la valeur NOT_SET    *
*********************** Entrées ***********************************
* ES: TableauChasse, E: sprites (pour le nombre de canards actifs *
*******************************************************************/

void initTableau(TableauChasse &tableau, Sprites sprites)
{
    for(int i = 0 ; i < sprites.canardActifs ; i++)
    {
        tableau.typeCanard[i] = NOT_SET;
    }
}

/****************** Nom de la fonction ****************************
* initFichiers                                                    *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* Ecrit NOT_SET (pour le nom) et 0 pour le score dans le fichier  *
******************************************************************/

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

/****************** Nom de la fonction ****************************
* initMessage                                                     *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* initialie la position, la police, la taille et le contenu de    *
* chaque message                                                  *
*********************** Entrées ***********************************
* ES: un tableau de message à initialiser                         *
*******************************************************************/

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
    msgs[MSG_SCORE_ROUGE].textColor.r = 255;
    msgs[MSG_SCORE_ROUGE].textColor.g = 0;
    msgs[MSG_SCORE_ROUGE].textColor.b = 0;

    msgs[MSG_0_TOUCHE].message = "AUCUN_CANARD_MORT";
    msgs[MSG_PAUSE].message = "Jeu en pause";
}

/****************** Nom de la fonction ****************************
* initBouton                                                      *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* initilise les boutons en affectant un contenu et en définissant *
* leur position                                                   *
*********************** Entrées ***********************************
* ES: une structure Boutons                                       *
*******************************************************************/
void initBouton(Boutons &boutons)
{
    boutons.bouton[BOUTON_PLAY].contenu = "Jouer";
    boutons.bouton[BOUTON_QUIT].contenu = "Quitter";
    boutons.bouton[BOUTON_REPRENDRE].contenu = "Reprendre";
    boutons.bouton[BOUTON_RETOUR].contenu = "Retour";
    boutons.bouton[BOUTON_SCORE].contenu = "High Score";
    boutons.bouton[BOUTON_OK].contenu = "OK";
    boutons.bouton[BOUTON_OPTIONS].contenu = "Options";
    boutons.bouton[BOUTON_THEME_CLASSIQUE].contenu = "Classique";
    boutons.bouton[BOUTON_THEME_ISLAND].contenu = "Island";
    for (int i = 0 ; i < 2 ; i++)
    {
        boutons.lecture[i].x = i * 226;
        boutons.lecture[i].y = 0;
        boutons.lecture[i].w = 216;
        boutons.lecture[i].h = 74;
    }
    for (int i=0; i<NB_BOUTONS_DIFFERENTS; i++)
    {
        boutons.bouton[i].actif = false;
    }
}

/****************** Nom de la fonction ****************************
* initSourisEvent                                                 *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* initialie tous les clics de la souris à non cliqué              *
*********************** Entrées ***********************************
* ES: une structure SourisEvent                                   *
*******************************************************************/

void initSourisEvent(SourisEvent &sourisEvent)
{
    sourisEvent.bl = sourisEvent.bm = sourisEvent.br = sourisEvent.bl2 = sourisEvent.bm2 = sourisEvent.br2 = false;
    sourisEvent.clicGauche = sourisEvent.clicDroit = sourisEvent.clicMolette = false;
}

/****************** Nom de la fonction ****************************
* initTime                                                        *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* initie une structure Time                                       *
*********************** Entrées ***********************************
* ES: une structure Time                                          *
*******************************************************************/

void initTime(Time &time)
{
    time.currentTime = SDL_GetTicks(); // le temps actuel T, SDL_GetTicks() renvoit le nombre de ms depuis l'exécution du programme
    time.fpsTime = (1 / (FPS_MAX * 1.0) * 1000); // Calcule en ms le temps entre chaque actualisation d'image à partir de la constante FPS_LIMIT.
    time.timeFps = 0; // le temps suivant T + 1 pour les fps, d'abord égal à 0 puis prendra la valeur de T, et T prendra la valeur T - 1
    time.menuTime = 2000; //temps d'affichage du niveau par exemple
    time.timeMenu = 0; // // le temps suivant T + 1 pour le menu, d'abord égal à 0 puis prendra la valeur de T, et T prendra la valeur T - 1
    time.keyTime = 700;
    time.timeKey = 0;
    time.defKeyTime = 100;
    time.timeDefKey = 0;
}


/****************** Nom de la fonction ****************************
* initPartie                                                      *
******************** Auteur , Dates *******************************
* Nom : JACQUOT, LE HO                                            *
********************* Description *********************************
* initie la partie                                                *
*********************** Entrées ***********************************
* ES: une structure partie, le nombre de canard                   *
*******************************************************************/

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


/****************** Nom de la fonction ****************************
* initChien                                                       *
******************** Auteur , Dates *******************************
* Nom : LE HO                                                     *
********************* Description *********************************
* initie le chien                                                 *
*********************** Entrées ***********************************
* ES: une structure chien                                         *
*******************************************************************/

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

/****************** Nom de la fonction ****************************
* initCanard                                                      *
******************** Auteur , Dates *******************************
* Nom : LE HO                                                     *
********************* Description *********************************
* initie les canards                                              *
*********************** Entrées ***********************************
* ES: une structure canard                                        *
*******************************************************************/

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


/****************** Nom de la fonction ****************************
* initHighScore                                                   *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* initie le plus grand score                                      *
*********************** Entrées ***********************************
* ES: un tableau HighScore                                        *
*******************************************************************/


void initHighScore(HighScore highScore[])
{
    for (int i=0; i<NB_HIGH_SCORE; i++)
    {
        highScore[i].nom = "";
        highScore[i].score = 0;
    }
}
