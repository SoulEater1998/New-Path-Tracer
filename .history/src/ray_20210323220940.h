#ifndef RAY_H
#define RAY_H

#include "vector.h"
using namespace DirectX;
using namespace DirectX::PackedVector;
struct Ray {
    XMFLOAT3 origin, direction;
    Ray(FXMVECTOR o_, FXMVECTOR d_){
        XMStoreFloat3(&origin, o_);
        XMStoreFloat3(&direction, d_);
    }
};

#endif // RAY_H