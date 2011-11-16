#pragma once
#include "SDL.h"
#include "vehicle.h"

class Logic {
    private:
        Vehicle v;
    public:
        Logic();
        void feed_key(SDL_keysym* key, int state);
        void draw_frame();
};
