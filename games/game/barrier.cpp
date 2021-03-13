#include "barrier.h"

barrier::barrier()
{
    PosX = 1300;
    PosY = 545;
}

void barrier::move()
{
    if (PosX < 0) PosX = 1300;
    PosX -= barrier_speed;
    barrier_speed+= 0.001;
}

/*void barrier::render(LTexture barrierTexture, SDL_Renderer* gRenderer)
{
    barrierTexture.render(PosX,PosY,NULL, gRenderer);
}*/

double barrier::x()
{
    return PosX;
}
double barrier::y()
{
    return PosY;
}
