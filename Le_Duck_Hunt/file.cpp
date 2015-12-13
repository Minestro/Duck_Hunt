#include "main.h"

bool testHighScore (std::string fichier, Partie &partie)
{
    bool newHS = false;
    int readScore;
    std::string readNom;
    std::fstream f1;
    f1.open(fichier.c_str(), std::ios::in);
    if(f1.fail())
    {
        std::cerr << "ouverture impossible du fichier des score" << std::endl;
        return 0;
    }
    f1 >> readNom;
    f1 >> readScore;
    while (!f1.eof() && !newHS)
    {
        if (readScore < partie.score)
        {
            newHS = true;
        }
        f1 >> readNom;
        f1 >> readScore;
    }
    f1.close();
    return newHS;
}

void getScore (std::string fichier, std::string &nom, std::string &score, int ligne)
{
    std::fstream f1;
    int i = 1;
    f1.open(fichier.c_str(), std::ios::in);
    if(f1.fail())
    {
        std::cerr << "ouverture impossible du fichier des score" << std::endl;
    }
    f1 >> nom;
    f1 >> score;
    while (!f1.eof() && i<ligne)
    {
        f1 >> nom;
        f1 >> score;

        i++;
    }
    f1.close();
}
