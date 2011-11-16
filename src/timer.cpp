// Note: stolen — https://github.com/tuxerr/City/blob/master/src/timer.cpp
// Hope you don't mind, tuxerr. ;]
#include "timer.h"
#include "log.h"

Timer::Timer(int fps) : fps(fps) , act_fps(fps) {
}

void Timer::init() {
    // inits SDL timer system
    SDL_InitSubSystem(SDL_INIT_TIMER);
    reset();
}

void Timer::reset() {
    last_time=SDL_GetTicks();
}

void Timer::wait() {
    SDL_Delay(1000/fps);return;
    // slows the program to avoid using too much CPU
    int act_time=SDL_GetTicks();
    int needed_time=1000/fps;

    if(act_time-last_time<needed_time) {
        // if the new image is too quick
        SDL_Delay(needed_time-act_time+last_time);
    } else {
        l("Performance issues : program cannot keep up to %i fps (act"
            "%i ms or %i fps)", act_time-last_time, act_fps);
    }

    act_time=SDL_GetTicks();

    // calculates real FPS
    if(act_time!=last_time)
        act_fps=1000/(act_time-last_time);

    last_time=act_time;
}

int Timer::get_act_fps() {
    return act_fps;
}
