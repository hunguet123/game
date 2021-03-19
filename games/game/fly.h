#ifndef FLY_H_
#define FLY_H
#include"BaseObject.h"
#include <ctime>
#include <algorithm>
class fly
{
    public:
        fly();
        void move(double fly_speed );

        void render(LTexture &flyTexture, SDL_Rect* clip, SDL_Renderer *gRenderer);

    private:
        double Fx;
        double Fy;
};

#endif // BIRD_H_
