#include "BaseObject.h"
#include "character.h"
#include "barrier.h"
#include "grass.h"
#include "checkCollision.h"
#include "fly.h"
#include <ctime>
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
LTexture DinosourTexture;
LTexture cactusTexture;
LTexture plotTexture;
LTexture treeTexture;
LTexture cloudsTexture;
LTexture birdTexture;


const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect CharacterClips[ WALKING_ANIMATION_FRAMES ];

const int BIRD_ANIMATION_FRAMES = 9;
SDL_Rect birdClips[ BIRD_ANIMATION_FRAMES ];

int main( int argc, char* args[] )
{
    srand(time(0));

character dinosaur;
barrier cactus[4];
grass plot;
grass Tree;
grass Clouds;
fly bird;
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

            int frame_charactor = 0;
            int frame_bird = 0;


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
				cactus[0].move(4);
                cactus[1].move(4);
                cactus[2].move(4);
                cactus[3].move(4);
                bird.move(6);
                plot.move(4);
                Tree.move(1.5);
				Clouds.move(0.5);


                if (check_collision_character_barrier(dinosaur, cactus[0]) || check_collision_character_barrier(dinosaur, cactus[1]) || check_collision_character_barrier(dinosaur, cactus[2] ) || check_collision_character_barrier(dinosaur, cactus[3]) )
                { dinosaur.stop();
                cactus[0].stop(4);
                cactus[1].stop(4);
                cactus[2].stop(4);
                cactus[3].stop(4);
                plot.stop(4);
                Tree.stop(1.5);
                Clouds.stop(0.5);
                bird.stop(6);
                frame_charactor--;
                frame_bird--;
                }

                if (check_collision_character_bird(dinosaur, bird))
                {
                     dinosaur.stop();
                cactus[0].stop(4);
                cactus[1].stop(4);
                cactus[2].stop(4);
                cactus[3].stop(4);
                plot.stop(4);
                Tree.stop(1.5);
                Clouds.stop(0.5);
                bird.stop(6);
                frame_charactor--;
                frame_bird--;
                }

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                double Cloud_x = Clouds.X()- 1280;
                double Cloud_y = Clouds.Y() - 535;
                cloudsTexture.render(Cloud_x, Cloud_y, NULL, gRenderer);
                cloudsTexture.render(Cloud_x + 1280, Cloud_y, NULL, gRenderer);
				Tree.render( treeTexture, gRenderer);

                SDL_Rect* currentClip = &CharacterClips[ frame_charactor/6 ];

                dinosaur.render(DinosourTexture, currentClip, gRenderer);

                cactus[0].render(cactusTexture, NULL, gRenderer);
                cactus[1].render(cactusTexture, NULL, gRenderer);
                cactus[2].render(cactusTexture, NULL, gRenderer);
                cactus[3].render(cactusTexture, NULL, gRenderer);


                SDL_Rect* birdCurrentClip = &birdClips[frame_bird/9 ];

                bird.render(birdTexture, birdCurrentClip, gRenderer );

                double plotX = plot.X() - 1280 ;
                double plotY = plot.Y() + 62;
                plotTexture.render(plotX,plotY,NULL,gRenderer);
                plotTexture.render(plotX + 1280,plotY,NULL,gRenderer);
				SDL_RenderPresent( gRenderer );
				++frame_charactor;
                ++frame_bird;
				if (frame_bird / 9 >= BIRD_ANIMATION_FRAMES ) frame_bird = 0;
				if( frame_charactor / 6 >= WALKING_ANIMATION_FRAMES )
				{
					frame_charactor = 0;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}


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
	bool success = true;

    DinosourTexture.loadFromFile( "img//char.png", gRenderer );
{
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
	birdTexture.loadFromFile("img//bird1.png", gRenderer);
    {
    int x = 0, y = 0;
    for (int i = 0; i < 9; i++)
    {
        birdClips[i].x = x;
        birdClips[i].y = y;
        birdClips[i].w = 80;
        birdClips[i].h = 80;
        x+= 80;
    }
    }
	cactusTexture.loadFromFile("img//cactus.png", gRenderer);
	plotTexture.loadFromFile("img//plot.png", gRenderer);
	treeTexture.loadFromFile("img//tree.png", gRenderer);
	cloudsTexture.loadFromFile("img//bk1.png", gRenderer);
	return success;
}

void close()
{
	//Free loaded images
	DinosourTexture.free();
    plotTexture.free();
    cloudsTexture.free();
    treeTexture.free();
    cactusTexture.free();
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
