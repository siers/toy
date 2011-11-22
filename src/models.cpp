#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "models.h"
#include "log.h"

Model::Model(const char* name)
    : visible(1)
{
    std::stringstream stream;
    stream << "models/" << name << ".bin";
    std::string path;
    stream >> path;
    face *f;
    int i;

    std::ifstream data(path.c_str(), std::ios::in);

    assert(!data.fail(), "Couldn't locate model: %s", name);

    while (data.good()) {
        f = new face;
        if (!data.read(&f->verts, sizeof(f->verts))) {
            break;
        }

        data.read(f->buf, sizeof(f->car[0]) * f->verts);
        log(MSG_DEBUG, "verts: %i", f->verts);
        for (i = 0; i < f->verts; i++) {
            log(MSG_DEBUG, "x: %3.3f, y: %3.3f, z: %3.3f",
                    f->car[i][0], f->car[i][1], f->car[i][2]);
        }
        faces.push_back(f);
    }

    l("Model `%s' loaded.", name);
    data.close();

    // Initialize variables.
    memset(t, 0, sizeof(t));
    memset(r, 0, sizeof(r));
    angle = 0;
}

void
Model::render()
{
    std::list<void*>::iterator it;
    face *f;
    int i, verts;

    if (!visible)
        return;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(t[0], t[1], t[2]);
    glRotatef(angle, r[0], r[1], r[2]);

    for (it = faces.begin(); it != faces.end(); it++) {
        f = (face*) *it;
        verts = f->verts;
        glBegin(verts == 3 ? GL_TRIANGLES : GL_QUADS);

        for (i = 0; i < verts; i++) {
            glColor3f(.2 * i, .1 * i, .23 * i);
            glVertex3f(f->car[i][0], f->car[i][1], f->car[i][2]);
        }

        glEnd();
    }
}
