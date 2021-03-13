#include "character.h"

character::character()
{
    //Initialize the offsets
    mPosX = 250;
    mPosY = 550;
}

void character::handleEvent( SDL_Event& e )
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
            status = JUMP;

        }
    }

}

void character::move()
{
    if (status == JUMP && mPosY >= 350)
	{
		mPosY += -CHARACTER_JUMP_SPEED;
	}
	if (mPosY <= 350)
	{
		status = FALL;
	}
	if (status == FALL && mPosY < 550)
	{
		mPosY += CHARACTER_FALL_SPEED;
	}
}


double character::PosX()
{
    //Show the dot
	return mPosX;
}
double character::PosY()
{
    return mPosY;
}

/*void character::render(LTexture character, SDL_Rect* clip, SDL_Renderer* gRenderer)
{
    character.render(mPosX, mPosY, clip, gRenderer);
}*/
