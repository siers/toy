#include <string.h>
#include <math.h>

#include "physical.h"
#include "log.h"

#define DEG2RAD M_PI / 180

PhysicalModel::PhysicalModel(const char* name)
    : Model(name)
{
    friction = 0.8;

    // Initialize vectors.
    memset((void*) buf, 0, sizeof(buf));
}

void PhysicalModel::tick()
{
    int i;

    v[X] = v[X] + a[X] * cos(angle * DEG2RAD) - a[Y] * sin(angle * DEG2RAD);
    v[Y] = v[Y] + a[X] * sin(angle * DEG2RAD) + a[Y] * cos(angle * DEG2RAD);
    for (i = 0; i < 3; i++) {
        v[i] *= friction;
        t[i] += v[i];
    }

    av = (av + aa) * friction;
    angle += av;
}
