#pragma once

#include <GL/gl.h>
#include <list>

enum {
    X, Y, Z
};

struct face {
    char verts; /* 3 or 4 */
    union {
        struct {
            // Here will lie color, normals, *.
            float car[4][3];
        };
        char buf[sizeof(float) * 12];
    };
};

class Model {
    private:
        std::list<void*> faces;
    public:
        // Translation values.
        float t[3];
        // Rotation values.
        float r[3];
        float angle;
        char visible;

        Model(const char* name);
        void render();
};
