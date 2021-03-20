#include "fly.h"

fly::fly()
{
    Fx = rand() % 500 + 1280;
    Fy = rand() % 145 + 400;
}

void fly::move(double speed)
{
    if (Fx < 0) {
        Fx = rand() % 500 + 1280;
        Fy = rand() % 145 + 400;
    }
    Fx -= speed;
    speed += 0.005;
}
void fly::stop(double speed)
{
    Fx += speed;
    speed += 0.005;
}

void fly::render(LTexture& birdTexture, SDL_Rect* clip, SDL_Renderer* gRenderer)
{
    birdTexture.render(Fx, Fy, clip, gRenderer);
}

double fly::X()
{
    return Fx;
}

double fly::Y()
{
    return Fy;
}
