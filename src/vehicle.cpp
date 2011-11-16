#include "vehicle.h"

Vehicle::Vehicle ()
    : PhysicalModel("vehicle")
{
}

void Vehicle::tick()
{
    PhysicalModel::tick();

    if (blink_times)
        if (++blink_tics == BLINK_PERIOD) {
            visible ^= 1;
            blink_times--;
            blink_tics = 0;
        }
}

void Vehicle::blink(int times)
{
    blink_times = times * 2 + 1;
    blink_tics = 0;
    visible = 0;
}
