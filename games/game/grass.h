#ifndef GRASS_H_
#define GRASS_H_
#include "BaseObject.h"

class grass
{
    public:

        grass();

        void move(double grass_speed );

        void render(LTexture &grassTexture, SDL_Renderer *gRenderer);

        double x();
        double y();
    private:
        double Gx;
        double Gy;
};


#endif // GRASS_H_
