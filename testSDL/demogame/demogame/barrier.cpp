#include "barrier.h"


barrier::barrier()
{

}

void barrier::move( double speed )
{
    if (PosX < 0) PosX = PosX + rand() % 300 + 1280;
    PosX -= speed;
}

void barrier::stop(double speed)
{
    PosX += speed;
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


