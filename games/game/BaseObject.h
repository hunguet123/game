#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path, SDL_Renderer* gRenderer );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( double x, double y, SDL_Rect* clip = NULL, SDL_Renderer* gRenderer = NULL );

		//Gets image dimensions
		double getWidth();
		double getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		double mWidth;
		double mHeight;
};

#endif // BASEOBJECT_H_
