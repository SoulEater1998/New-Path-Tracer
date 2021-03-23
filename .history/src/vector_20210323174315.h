#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>
#include <math.h>
#include <stdint.h>
#include <windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
// Vector 3
struct Vec : XMFLOAT3 {
    
    Vec(float x_ = 0, float y_ = 0, float z_ = 0) : XMFLOAT3(x_, y_, z_) {}

    // Return x,y, and z component for 0, 1, and 2 respectively
    float axis(uint32_t axis){
        if (axis == 0) return x;
        if (axis == 1) return y;
        if (axis == 2) return z;
    }
};

#endif // VECTOR_H