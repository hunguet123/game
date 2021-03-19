#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "BaseObject.h"


#define JUMP 1
#define FALL 2

class character
{
    public:

		static const int CHARACTER_JUMP_SPEED = 8;
		static const int CHARACTER_FALL_SPEED = 8;


		character();


		void handleEvent( SDL_Event& e );


		void move();


        void render(LTexture &character, SDL_Rect* clip, SDL_Renderer* gRenderer);
    private:

		double mPosX, mPosY;

		int status;

};


#endif
