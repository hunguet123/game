#ifndef BARRIER_H_
#define BARRIER_H_

#include "BaseObject.h"

class barrier
{
    public:
        double barrier_speed = 3;

        barrier();

        void move();
        double y();
        double x();
        //void render(LTexture barrierTexture, SDL_Renderer* gRenderer);
    private:
        double PosY;
        double PosX;

};


#endif // BARRIER_H_
