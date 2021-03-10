#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "BaseObject.h"


#define JUMP 1
#define FALL 2

class character
{
    public:
		//The dimensions of the dot
		static const int CHARACTER_JUMP_SPEED = 8;
		static const int CHARACTER_FALL_SPEED = 8;

		//Initializes the variables
		character();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		double PosX();
		double PosY();
        //void render(LTexture character, SDL_Rect* clip, SDL_Renderer* gRenderer);
    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		int status;

};


#endif
