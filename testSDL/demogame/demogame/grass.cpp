#include "grass.h"

grass::grass()
{
    Gx = 1280;
    Gy = 535;
}

void grass::move(double grass_speed )
{
    if (Gx < 0 ) Gx = 1280;
    Gx -= grass_speed;
    grass_speed += 0.005;
}

void grass::render(LTexture &grassTexture, SDL_Renderer* gRenderer )
{
    grassTexture.render(Gx, Gy, NULL, gRenderer);
    grassTexture.render(Gx - 1280, Gy, NULL, gRenderer);
}

double grass::x()
{
    return Gx;
}

double grass::y()
{
    return Gy;
}
