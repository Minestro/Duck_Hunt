#include "images.h"


/****************** Nom de la fonction ****************************
* load_image                                                      *
******************** Auteur , Dates *******************************
* Nom : MOODLE                                                    *
********************* Description *********************************
*                                                                 *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/

SDL_Surface *load_image( std::string filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    //Return the optimized image
    return optimizedImage;
}

// -- loadImageWithColorKey ---------------------
// chargement d'une image
// * paramètres entrées :
// - "filename" : nom de l'image
// - "r,g,b"    : couleur de la ColorKey; cette
//   couleur devient transparente !
// * paramètre de sortie : SDL_Surface contenant
//   l'image.
// ----------------------------------------------



/****************** Nom de la fonction ****************************
* loadImageWithColorKey                                           *
******************** Auteur , Dates *******************************
* Nom : MOODLE                                                    *
********************* Description *********************************
*                                                                 *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/


SDL_Surface *loadImageWithColorKey(std::string filename, int r, int g, int b)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());
    if(loadedImage == NULL)
    {
        std::cout << "Problème lors d'un chargement d'image : " << filename << std::endl;
    }

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );

        //If the image was optimized just fine
        if( optimizedImage != NULL )
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, r, g, b );

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
        else
        {
            std::cout << "Problème lors d'un chargement d'image : " << filename << std::endl;
            exit(EXIT_FAILURE);
        }


    }
    //Return the optimized image
    return optimizedImage;
}



/****************** Nom de la fonction ****************************
* chargerImages                                                   *
******************** Auteur , Dates *******************************
* Nom : JACQUOT, LE HO                                            *
********************* Description *********************************
* Charge les images                                               *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/


/*** fonction qui charge les images ***/

void chargerImages(Sprites &sprites, Chien &chien, Boutons &boutons, std::string theme)
{
    SDL_Rect initializer;
    initializer.x = initializer.y = 0;

    boutons.source = loadImageWithColorKey("sprites/"+theme+"/boutons.bmp", 0, 0, 0);

    sprites.background.source = load_image("sprites/"+theme+"/backGame.png");
    sprites.background.position = initializer;

    sprites.background_blit.source = loadImageWithColorKey("sprites/"+theme+"/backGameBlit.png", 0, 0, 0);
    sprites.background_blit.position = initializer;

    sprites.background_menu.source = load_image("sprites/"+theme+"/menu.png");
    sprites.background_menu.position = initializer;

    sprites.viseur.source = loadImageWithColorKey("sprites/"+theme+"/viseur.png", 0, 0, 0);
    sprites.hits.source = loadImageWithColorKey("sprites/"+theme+"/hit.png", 0, 0, 0);
    sprites.hits.lecture.x = 5;
    sprites.hits.lecture.y = 5;
    sprites.hits.lecture.w = 27;
    sprites.hits.lecture.h = 27;
    sprites.hits.position.y = 665;

    sprites.shots.source = load_image("sprites/"+theme+"/shot.png");
    sprites.shots.lecture = initializer;
    sprites.shots.position.x = 65;
    sprites.shots.position.y = 658;
    sprites.shots.lecture.w = 75;
    sprites.shots.lecture.h = 50;

    if (theme == "classique")
    {
        sprites.canardSprite[DARK] = loadImageWithColorKey("sprites/"+theme+"/canardNoir.png", 228, 255, 0);
        sprites.canardSprite[CHESNUT] = loadImageWithColorKey("sprites/"+theme+"/canardMarron.png", 228, 255, 0);
        sprites.canardSprite[BLOOD] = loadImageWithColorKey("sprites/"+theme+"/canardRouge.png", 228, 255, 0);
        sprites.canardSprite[BLUISH_PURPLE] = loadImageWithColorKey("sprites/"+theme+"/canardViolet.png", 228, 255, 0);
    } else if (theme== "island") {
        sprites.canardSprite[DARK] = loadImageWithColorKey("sprites/"+theme+"/canardNoir.png", 0, 255, 255);
        sprites.canardSprite[CHESNUT] = loadImageWithColorKey("sprites/"+theme+"/canardMarron.png", 0, 0, 0);
        sprites.canardSprite[BLOOD] = loadImageWithColorKey("sprites/"+theme+"/canardRouge.png", 0, 0, 0);
        sprites.canardSprite[BLUISH_PURPLE] = loadImageWithColorKey("sprites/"+theme+"/canardViolet.png", 0, 0, 0);
    }

    sprites.points.source = loadImageWithColorKey("sprites/"+theme+"/points.png", 0, 0, 0);
    sprites.points.lecture.h = 17;
    sprites.points.lecture.w = 32;
    sprites.points.lecture.x = 0;

    chien.image[CHIEN_MARCHE].source = loadImageWithColorKey("sprites/"+theme+"/chienMarche.png", 0, 255, 0);
    chien.image[CHIEN_MARCHE].lecture.h = 87;
    chien.image[CHIEN_MARCHE].lecture.w = 120;

    chien.image[CHIEN_CONTENT].source = loadImageWithColorKey("sprites/"+theme+"/chienContent.png", 0, 255, 0);
    chien.image[CHIEN_CONTENT].lecture.h = 100;
    chien.image[CHIEN_CONTENT].lecture.w = 113;

    chien.image[CHIEN_SAUTE_1].source = loadImageWithColorKey("sprites/"+theme+"/chienSaute1.png", 0, 255, 0);
    chien.image[CHIEN_SAUTE_1].lecture.h = 100;
    chien.image[CHIEN_SAUTE_1].lecture.w = 94;

    chien.image[CHIEN_SAUTE_2].source = loadImageWithColorKey("sprites/"+theme+"/chienSaute2.png", 0, 255, 0);
    chien.image[CHIEN_SAUTE_2].lecture.h = 95;
    chien.image[CHIEN_SAUTE_2].lecture.w = 110;

    chien.image[CHIEN_RIGOLE].source = loadImageWithColorKey("sprites/"+theme+"/chienMoqueur.png", 228, 255, 0);
    chien.image[CHIEN_RIGOLE].lecture.h = 78;
    chien.image[CHIEN_RIGOLE].lecture.w = 58;

    chien.image[CHIEN_CONTENT_SIMPLE].source = loadImageWithColorKey("sprites/"+theme+"/chienContentSimple.png", 228, 255, 0);
    chien.image[CHIEN_CONTENT_SIMPLE].lecture.h = 80;
    chien.image[CHIEN_CONTENT_SIMPLE].lecture.w = 90;

    chien.image[CHIEN_CONTENT_DOUBLE].source = loadImageWithColorKey("sprites/"+theme+"/chienContentDouble.png", 0, 255, 0);
    chien.image[CHIEN_CONTENT_DOUBLE].lecture.h = 80;
    chien.image[CHIEN_CONTENT_DOUBLE].lecture.w = 112;
}


/****************** Nom de la fonction ****************************
* libererImages                                                   *
******************** Auteur , Dates *******************************
* Nom : JACQUOT                                                   *
********************* Description *********************************
* Libère les images de la mémoire                                 *
*********************** Entrées ***********************************
* ES:                                                             *
*******************************************************************/

void libererImages(Sprites &sprites, Chien &chien, Boutons &boutons)
{
    SDL_FreeSurface(boutons.source);
    SDL_FreeSurface(sprites.background_menu.source);
    SDL_FreeSurface(sprites.background.source);
    SDL_FreeSurface(sprites.background_blit.source);
    SDL_FreeSurface(sprites.viseur.source);
    SDL_FreeSurface(sprites.hits.source);
    SDL_FreeSurface(sprites.shots.source);
    SDL_FreeSurface(sprites.canardSprite[DARK]);
    SDL_FreeSurface(sprites.canardSprite[CHESNUT]);
    SDL_FreeSurface(sprites.canardSprite[BLOOD]);
    SDL_FreeSurface(sprites.canardSprite[BLUISH_PURPLE]);
    SDL_FreeSurface(sprites.points.source);
    SDL_FreeSurface(chien.image[CHIEN_MARCHE].source);
    SDL_FreeSurface(chien.image[CHIEN_CONTENT].source);
    SDL_FreeSurface(chien.image[CHIEN_SAUTE_1].source);
    SDL_FreeSurface(chien.image[CHIEN_SAUTE_2].source);
    SDL_FreeSurface(chien.image[CHIEN_RIGOLE].source);
    SDL_FreeSurface(chien.image[CHIEN_CONTENT_SIMPLE].source);
    SDL_FreeSurface(chien.image[CHIEN_CONTENT_DOUBLE].source);
}
