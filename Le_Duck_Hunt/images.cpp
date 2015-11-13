#include "images.h"

SDL_Surface *chargerUneImage(string nomFichier)
{
    SDL_Surface *image = NULL;
    SDL_Surface *imageOptimisee = NULL;
    /* Ouverture de l'image */
    image = IMG_Load(nomFichier.c_str());
    if(image == NULL)
    {
        cerr << "Erreur IMG_Load" << endl;
        exit(EXIT_FAILURE);
    }
    if(image->flags & SDL_SRCALPHA)
    {
        imageOptimisee = SDL_DisplayFormatAlpha(image);
    }
    else
    {
        imageOptimisee = SDL_DisplayFormat(image);
    }

    if(imageOptimisee == NULL)
    {
        cerr << "Erreur impossible d'optimiser l'image" << endl;
    }

    SDL_FreeSurface(image);

    return imageOptimisee;
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

SDL_Surface *loadImageWithColorKey(string filename, int r, int g, int b)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

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
     }
    //Return the optimized image
    return optimizedImage;
}


/*** fonction qui charge les images ***/
void charger(Images &i)
{
    i.backGame.image = chargerUneImage("sprites/backGame.png");
    i.backGameBlit.image = loadImageWithColorKey("sprites/backGameBlit.png", 0, 0, 0);
    i.duck.image = chargerUneImage("sprites/duck.png"); // à découper
    i.hit.image = chargerUneImage("sprites/hit.png");
    i.menu.image = chargerUneImage("sprites/menu.png");
    i.points.image = chargerUneImage("sprites/points.png");
    i.shot.image = chargerUneImage("sprites/shot.png");
    i.viseur.image = chargerUneImage("sprites/viseur.png");
}

void placer(Images &i)
{
    i.backGame.x = (SDL_GetVideoSurface()->w - i.backGame.image->w) / 2;
    i.backGame.y = (SDL_GetVideoSurface()->h - i.backGame.image->h) / 2;
    i.backGameBlit.x = (SDL_GetVideoSurface()->w - i.backGameBlit.image->w) / 2;
    i.backGameBlit.y = (SDL_GetVideoSurface()->h - i.backGameBlit.image->h) / 2;
}

void libererImages(Images i)
{
    SDL_FreeSurface(i.backGame.image);
    SDL_FreeSurface(i.backGameBlit.image);
    SDL_FreeSurface(i.duck.image);
    SDL_FreeSurface(i.hit.image);
    SDL_FreeSurface(i.menu.image);
    SDL_FreeSurface(i.points.image);
    SDL_FreeSurface(i.shot.image);
    SDL_FreeSurface(i.viseur.image);
}
