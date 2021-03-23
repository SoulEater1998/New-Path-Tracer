#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct Ray {
    XMFLOAT3 origin, direction, direction_inv;
    Ray(XMFLOAT3 o_, XMFLOAT3 d_) : origin(o_), direction(d_) {
        direction_inv = XMFLOAT3(
                1./direction.x,
                1./direction.y,
                1./direction.z
        );
    }
};

#endif // RAY_H