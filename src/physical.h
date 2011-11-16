#pragma once

#include "models.h"

class PhysicalModel: public Model {
    public:
        union {
            struct {
                float v[3]; // Translation vectors.
                float a[3]; // Translation vec acceleration.
                float av;   // Angular velocity.
                float aa;   // Angular acceleration.
            };
            float buf[12];
        };
        float friction;

        PhysicalModel(const char* name);
        void tick();
};
