#pragma once
#include "SDL.h"
#include "logic.h"
#include "timer.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

class Scene {
    private:
        SDL_Surface *surface;

        int video_flags;
        void init_gl();
        void draw_floor();
    public:
        Timer timer;

        Scene();
        Logic logic;
        void run();
};
