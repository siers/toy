#include "logic.h"
#include "log.h"

Logic::Logic()
{
    m = new Model("vehicle");
    m->t[Z] = -10;
    v.t[Z] = -10;
    v.friction = 0.9;
    v.r[Z] = 1;
}

void Logic::feed_key(SDL_keysym* key, int state)
{
    float *target;
    char sign = 1;
    float coeff = 0.1;

    switch (key->sym) {
        case 'w':
            target = &v.a[X];
            break;
        case 's':
            target = &v.a[X];
            sign = -1;
            break;
        case 'a':
            target = &v.aa;
            coeff = 0.5;
            break;
        case 'd':
            target = &v.aa;
            coeff = 0.5;
            sign = -1;
            break;
        case 'r':
            v.v[X] = 0;
            v.v[Y] = 0;
            v.t[X] = 0;
            v.t[Y] = 0;
            v.av   = 0;
            v.blink(2);
        default:
            return;
    }

    if (state == SDL_KEYDOWN)
        *target = coeff * sign;
    else
        *target = 0;
}

void Logic::draw_frame()
{
    v.tick();
    v.render();
    m->render();
}
