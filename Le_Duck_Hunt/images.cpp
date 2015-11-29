#include "main.h"

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
        exit(EXIT_FAILURE);
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


/*** fonction qui charge les images ***/

void chargerImages(Sprites &sprites, Boutons &bouton)
{
    sprites.hit.source = load_image("sprites/hit.png");
    bouton.source = loadImageWithColorKey("sprites/bouton.bmp",0,0,0);
    sprites.background_menu.source = load_image("sprites/menu.png");

    sprites.background.source=load_image("sprites/backGame.png");
    sprites.background.position.x = 0;
    sprites.background.position.y = 0;

    sprites.background_blit.source=loadImageWithColorKey("sprites/backGameBlit.png", 0, 0, 0);
    sprites.background_blit.position.x = 0;
    sprites.background_blit.position.y = 0;

    sprites.background_menu.source=load_image("sprites/menu.png");
    sprites.viseur.source=loadImageWithColorKey("sprites/viseur.png",0,0,0);
    sprites.shots.source=load_image("sprites/shot.png");
    sprites.shots.position.x=65;
    sprites.shots.position.y=658;
    sprites.shots.lecture.w=75;
    sprites.shots.lecture.h=50;
    sprites.shots.lecture.y=0;
}

/*void libererImages(Sprites i)
{
   //A faire
}*/
