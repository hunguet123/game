#include "fly.h"

fly::fly()
{
    Fx = rand()% 2400 + 1280;
    Fy = rand() % 100 + 440;
}

void fly::move(double fly_speed )
{
    if(Fx < 0) { Fx = rand()% 2400 + 1280; Fy = rand() % 100 + 440;}
    Fx -= fly_speed;
    fly_speed += 0.005;
}

void fly::render(LTexture &flyTexture, SDL_Rect* clip, SDL_Renderer *gRenderer )
{
    flyTexture.render(Fx, Fy, clip, gRenderer);
}
