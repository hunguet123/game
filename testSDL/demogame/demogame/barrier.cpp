#include "barrier.h"


barrier::barrier()
{
    PosX = rand() % 1000 + 1280;
    PosY = 545;
}


void barrier::move( double speed )
{
    if (PosX < 0) PosX = rand() % 1000 + 1280;
    PosX -= speed;
    speed+= 0.005;

}

void barrier::stop(double speed)
{
    PosX += speed;
    speed += 0.005;
}
void barrier::render(LTexture &barrierTexture, SDL_Rect* clips, SDL_Renderer* gRenderer)
{
    barrierTexture.render(PosX,PosY, clips, gRenderer);
}

double barrier::X()
{
    return PosX;
}
double barrier::Y()
{
    return PosY;
}


