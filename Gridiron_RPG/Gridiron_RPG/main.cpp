/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "SimulationEngine.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 640;

//The frames per second
const int FRAMES_PER_SECOND = 60;

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

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
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
    bool success = true;

    //Nothing to load
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

	simulation::Game simmedGame;
	simulation::SimulateGame(simmedGame);

	//Keep track of the current frame
    int frame = 0;

    //Whether or not to cap the frame rate
    bool cap = true;

    //The frame rate regulator
    Timer fps;

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

			SDL_Texture* player_texture = loadTexture("..\\..\\assets\\dude01_grey.png");
			SDL_Texture* ball_texture = loadTexture("..\\..\\assets\\ball01.png");

			simulation::Play currentPlay = *simmedGame.begin();
			vector<Frame*>::iterator itFrame = currentPlay.begin();

			//While application is running
			while( !quit )
			{
				//Start the frame timer
				fps.start();

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

				for(vector<PlayerSnapshot>::iterator itPlayer = (*itFrame)->BeginPlayers(); itPlayer != (*itFrame)->EndPlayers(); itPlayer++) {
					PlayerLocation loc = (*itPlayer).loc;
                    double rotation = (*itPlayer).rotation + 180;
					if ((*itPlayer).fHasBall)
					{
						int xValue = static_cast<int>(1440*(loc.first/360.0))-5;
						int yValue = static_cast<int>(640*(loc.second/160.0))-15;
						SDL_Rect renderQuad = { xValue, yValue, 20, 15 };
						SDL_RenderCopy( gRenderer, ball_texture, NULL, &renderQuad);
					}


					int xValue = static_cast<int>(1440*(loc.first/360.0))-15;
					int yValue = static_cast<int>(640*(loc.second/160.0))-15;

					SDL_Rect renderQuad = { xValue, yValue, 30, 30 };

					SDL_RenderCopyEx( gRenderer, player_texture, NULL, &renderQuad, rotation, NULL, SDL_FLIP_NONE);			
				}
				

                //Update screen
                SDL_RenderPresent( gRenderer );

				if (itFrame != currentPlay.end() - 1)
					itFrame++;

				//Increment the frame counter
				frame++;
				//If we want to cap the frame rate
				if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
				{
					//Sleep the remaining frame time
					SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}