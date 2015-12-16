#include "main.h"

bool testHighScore (std::string fichier, Partie &partie)
{
    bool newHS = false;
    int i=0;
    getScore(fichier, partie.highScore);
    while (i<NB_HIGH_SCORE && !newHS)
    {
        if (partie.highScore[i].score < partie.score)
        {
            newHS = true;
        }
        i++;
    }
    return newHS;
}

void getScore (std::string fichier, HighScore highScore[])
{
    for (int i=0; i<NB_HIGH_SCORE; i++)
    {
        highScore[i].score = 0;
        highScore[i].nom = "Not_Set";
    }
    std::fstream f1;
    int i = 0;
    f1.open(fichier.c_str(), std::ios::in);
    if(f1.fail())
    {
        std::cerr << "ouverture impossible du fichier des score" << std::endl;
    }
    do
    {
        f1 >> highScore[i].nom;
        f1 >> highScore[i].score;
        i++;
    }
    while ((i<NB_HIGH_SCORE)&&(!f1.eof()));
    triScore(highScore, 0, NB_HIGH_SCORE-1);
    f1.close();

    f1.open(fichier.c_str(), std::ios::out);
    if(f1.fail())
    {
        std::cerr << "ouverture impossible du fichier des score" << std::endl;
    }
    for (int i=0; i<NB_HIGH_SCORE; i++)
    {
        f1 << highScore[i].nom;
        f1 << " ";
        f1 << highScore[i].score;
        f1 << " ";
    }
    f1.close();
}

void addScore (std::string fichier, std::string nom, int score, HighScore highScore[])
{
    std::fstream f1;
    HighScore highScoreTmp[NB_HIGH_SCORE+1];
    getScore(fichier.c_str(), highScoreTmp);
    highScoreTmp[NB_HIGH_SCORE].nom = nom;
    highScoreTmp[NB_HIGH_SCORE].score = score;
    triScore(highScoreTmp, 0, NB_HIGH_SCORE);
    f1.open(fichier.c_str(), std::ios::out);
    if(f1.fail())
    {
        std::cerr << "ouverture impossible du fichier des score" << std::endl;
    }
    for (int i=0; i<NB_HIGH_SCORE; i++)
    {
        highScore[i].nom = highScoreTmp[i].nom;
        highScore[i].score = highScoreTmp[i].score;
        f1 << highScore[i].nom;
        f1 << " ";
        f1 << highScore[i].score;
        f1 << " ";
    }
    f1.close();
}

void triScore (HighScore highScore[],  int debut, int fin)
{
    int pivot;
    if(fin > debut)
    {
        pivot = separer(highScore, debut, fin);
        triScore(highScore, debut, pivot - 1);
        triScore(highScore, pivot + 1, fin);
    }
}

int separer(HighScore highscore[], int debut, int fin)
{
    int sep, i;
    echangerTabHS(highscore, (debut + fin) / 2, fin);
    sep = debut;
    for(i = sep ; i < fin ; i++)
    {
        if(highscore[i].score > highscore[fin].score)
        {
            echangerTabHS(highscore, i, sep);
            sep++;
        }
    }
    echangerTabHS(highscore, fin, sep);

    return sep;
}

void echangerTabHS(HighScore highScore[], int pos1, int pos2)
{
    HighScore temp;
    temp = highScore[pos1];
    highScore[pos1] = highScore[pos2];
    highScore[pos2] = temp;
}
