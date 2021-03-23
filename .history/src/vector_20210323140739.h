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
struct Vec {
    float x,y,z;

    Vec(float x_=0, float y_=0, float z_=0):x{
    }

    // Return x,y, and z component for 0, 1, and 2 respectively
    float axis(uint32_t axis){
        if (axis == 0) return x;
        if (axis == 1) return y;
        if (axis == 2) return z;
        switch (axis){
        case 0:
            return vec3.x;
        case 1:
            return vec3.y;
        case 2:
            return vec3.z;
        default:
            return 0;
        }
    }

    // Vector operations
    Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); }        // Addition
    Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); }        // Subtraction
    Vec operator*(float b) const { return Vec(x*b,y*b,z*b); }                  // Multiplaction with scalar
    Vec operator/(float b) const { return Vec(x/b,y/b,z/b); }                   // Division with scalar
    Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); }             // Multiplication
    Vec& norm(){ return *this = *this * (1/sqrt(x*x+y*y+z*z)); }                // Normalise vector
    float dot(const Vec &b) const { return x*b.x+y*b.y+z*b.z; }                // Dot product
    Vec operator%(Vec&b){return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}      // Cross product
    Vec cross(const Vec&b){return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}    // Cross product
    float mag() const{return sqrt(x*x+y*y+z*z);}                               // Calculate vector magnitude
};

#endif // VECTOR_H