#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "BaseObject.h"
//The dot that will move around on the screen
class character
{
    public:
		//The dimensions of the dot
		static const int CHARACTER_WIDTH = 20;
		static const int CHARACTER_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int CHARACTER_VEL = 2;

		//Initializes the variables
		character();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		double PosX();
		double PosY();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};


#endif
