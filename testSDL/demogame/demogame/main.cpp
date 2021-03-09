#include "BaseObject.h"
#include "character.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;
LTexture gBackground;
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
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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

	//Load dot texture
	if( !gDotTexture.loadFromFile( "char.png", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
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
	gBackground.loadFromFile("bk2.png", gRenderer);
	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
    gBackground.free();
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

			character dinosaur;
            int frame = 0;
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
					dinosaur.handleEvent( e );
				}

				dinosaur.move();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				gBackground.render(0,0,NULL, gRenderer);
                SDL_Rect* currentClip = &CharacterClips[ frame/6 ];
				//Render Foo' to the screen
                double PosX = dinosaur.PosX();
                double PosY = dinosaur.PosY();
                gDotTexture.render(PosX, PosY,currentClip, gRenderer);
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

