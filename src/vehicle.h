#pragma once

#include "physical.h"
#define BLINK_PERIOD 13

class Vehicle: public PhysicalModel {
    private:
        int blink_times, blink_tics;
    public:
        Vehicle();
        void tick();
        void blink(int);
};
