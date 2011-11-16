#pragma once

#include "SDL.h"

extern int FPS;

class Timer {
public:
    Timer(int fps=FPS);
    void init();
    void reset();
    void wait();
    int get_act_fps();

private:
    int fps;
    int last_time;
    int act_fps;
};
