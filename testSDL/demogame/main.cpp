#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "BaseObject.h"
#include "Dot.h"


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//Scene textures
LTexture Character;
LTexture gBackgroundTexture;
const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect CharacterClips[ WALKING_ANIMATION_FRAMES ];

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
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

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
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_PRESENTVSYNC );
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

	//Load Foo' texture
	if( !Character.loadFromFile( "img//char.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
    else
    {
        //Set sprite clips
        int x = 0, y = 0;
        for (int i = 0; i < 6; ++i)
        {
		CharacterClips[ i ].x =   x;
		CharacterClips[ i ].y =   y;
		CharacterClips[ i ].w =  57;
		CharacterClips[ i ].h =  57;
		x+= 57;
        }
	}

	//Load background texture
	if( !gBackgroundTexture.loadFromFile( "img//bk2.png", gRenderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	Character.free();
	gBackgroundTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

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

            Dot dot;
            int frame = 0;
            bool stand = true;
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
					dot.handleEvent(e);
				}

                dot.move();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background texture to screen
                gBackgroundTexture.render(0,0 , NULL, gRenderer, 0.0, NULL, SDL_FLIP_NONE );

                SDL_Rect* currentClip = &CharacterClips[ frame/6 ];
				//Render Foo' to the screen
                dot.render(Character, currentClip);
                //Character.render(0,0 , gRenderer, currentClip);
				SDL_RenderPresent( gRenderer );
				++frame;

				//Cycle animation
				if( frame / 6 >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}