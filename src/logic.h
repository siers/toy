#pragma once
#include "SDL.h"
#include "vehicle.h"

class Logic {
    public:
        Vehicle v;
        Model *m;
        Logic();
        void feed_key(SDL_keysym* key, int state);
        void draw_frame();
};
