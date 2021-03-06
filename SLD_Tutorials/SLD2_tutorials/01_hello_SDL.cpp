<<<<<<< HEAD
=======
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
>>>>>>> 628584a794601d648022da98099c1e9d8819e983
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 640;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

<<<<<<< HEAD
//Loads individual image
SDL_Surface* loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}
=======
//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;
>>>>>>> 628584a794601d648022da98099c1e9d8819e983

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		 //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
<<<<<<< HEAD
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
=======
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
>>>>>>> 628584a794601d648022da98099c1e9d8819e983
                success = false;
            }
            else
            {
<<<<<<< HEAD
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
=======
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
>>>>>>> 628584a794601d648022da98099c1e9d8819e983
            }
        }
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
    bool success = true;

<<<<<<< HEAD
    gStretchedSurface = loadSurface("06_extension_libraries_and_loading_other_image_formats/loaded.bmp");
    if( gStretchedSurface == NULL )
	{
		printf( "Failed to load stretching image!\n" );
		success = false;
	}

=======
    //Nothing to load
>>>>>>> 628584a794601d648022da98099c1e9d8819e983
    return success;
}

void close()
{
	//Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

//SDL_Surface* loadSurface( std::string path )
//{
//	//The final optimized image
//	SDL_Surface* optimizedSurface = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//	if( loadedSurface == NULL )
//	{
//		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
//	}
//	else
//	{
//		//Convert surface to screen format
//		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
//		if( optimizedSurface == NULL )
//		{
//			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface( loadedSurface );
//	}
//
//	return optimizedSurface;
//}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

				//Draw blue horizontal line
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
                SDL_RenderDrawLine( gRenderer, SCREEN_WIDTH/12, 0, SCREEN_WIDTH/12, SCREEN_HEIGHT);

				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
                SDL_RenderDrawLine( gRenderer, 11*SCREEN_WIDTH/12, 0, 11*SCREEN_WIDTH/12, SCREEN_HEIGHT);

				int x = 10;
				for (int i = 3; i < 22; i++) 
				{
					SDL_RenderDrawLine( gRenderer, i*SCREEN_WIDTH/24, x, i*SCREEN_WIDTH/24, SCREEN_HEIGHT - x);
				}

				for (int i = 1; i < 100; i++) 
				{
					SDL_RenderDrawLine( gRenderer, SCREEN_WIDTH/12 + i*12, SCREEN_HEIGHT/2 - 30, SCREEN_WIDTH/12 + i*12, SCREEN_HEIGHT/2 - 25);
					SDL_RenderDrawLine( gRenderer, SCREEN_WIDTH/12 + i*12, SCREEN_HEIGHT/2 + 30, SCREEN_WIDTH/12 + i*12, SCREEN_HEIGHT/2 + 25);
				}

				//Draw vertical line of yellow dots
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
                for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
                {
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
                }

                //Update screen
                SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}