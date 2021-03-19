#ifndef BARRIER_H_
#define BARRIER_H_
#include "BaseObject.h"
#include<ctime>
#include<algorithm>
class barrier
{
    public:

        barrier();
        void move(double speed);
        double y();
        double x();
        void render(LTexture &barrierTexture, SDL_Rect* clips, SDL_Renderer* gRenderer);
    private:
        double PosY;
        double PosX;

};


#endif // BARRIER_H_
