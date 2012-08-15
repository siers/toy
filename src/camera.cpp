#include "camera.h"
#include "log.h"

void
Camera::position(Vehicle v)
{
    float
        near   = 3,
        far    = 1000,
        left   = -0.5,
        right  = 0.5,
        bottom = -1,
        top    = 1,
        m[16];


    m[0]  = 2 * near / (right - left);
    m[1]  = 0;
    m[2]  = (right + left) / (right - left);
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = 2 * near / (top - bottom);
    m[6]  = (top + bottom) / (top - bottom);
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = - (far + near) / (far - near);
    m[11] = - (2 * far * near) / (far - near);

    m[12] = 0;
    m[13] = 0;
    m[14] = -1;
    m[15] = 0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(m);
    glRotated(45, -1, 0, 0); // Rotate the camera a bit.
    glRotated(-v.angle + 90, 0, 0, 1); // Rotate it correctly.
    glTranslatef(-v.t[X], -v.t[Y], 0); // Set the hover to 0,0,0.
}
