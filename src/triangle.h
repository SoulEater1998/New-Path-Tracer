#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <algorithm>
#include <cfloat>

#include "vector.h"
#include "aabbox.h"
#include "material.h"
using namespace std;

struct Triangle {
    XMFLOAT3 v0, v1, v2;    // Vertex world space coordinates
    XMFLOAT3 n;             // Normal 
    XMFLOAT2 t0, t1, t2;    // Triangle texture coordinates
    Material *m;            // Pointer to material

    Triangle(
        FXMVECTOR v0_, FXMVECTOR v1_, FXMVECTOR v2_, 
        CXMVECTOR t0_= XMVectorZero(), 
        CXMVECTOR t1_= XMVectorZero(), 
        CXMVECTOR t2_= XMVectorZero(), 
        Material *m_ = NULL){
        XMStoreFloat3(&v0, v0_);
        XMStoreFloat3(&v1, v1_);
        XMStoreFloat3(&v2, v2_);
        XMStoreFloat2(&t0, t0_);
        XMStoreFloat2(&t1, t1_);
        XMStoreFloat2(&t2, t2_);
        XMStoreFloat3(&n, XMVector3Cross(v1_ - v0_, v2_ - v0_));
        m=m_;
    }

    // Returns axis aligned bounding box that contains the triangle
    AABBox get_bounding_box(){
        XMFLOAT3 bl = XMFLOAT3(
            min(min(v0.x, v1.x), v2.x),
            min(min(v0.y, v1.y), v2.y),
            min(min(v0.z, v1.z), v2.z)
        );
        XMFLOAT3 tr = XMFLOAT3(
            max(max(v0.x, v1.x), v2.x),
            max(max(v0.y, v1.y), v2.y),
            max(max(v0.z, v1.z), v2.z)
        );

        return AABBox(bl, tr);
    }

    // Returns the midpoint of the triangle
    XMVECTOR get_midpoint() {
        XMVECTOR xv0 = XMLoadFloat3(&v0);
        XMVECTOR xv1 = XMLoadFloat3(&v1);
        XMVECTOR xv2 = XMLoadFloat3(&v2);
        return (xv0 + xv1 + xv2) / 3;
    }

    // Checks if ray intersects with triangle. Returns true/false.
    bool intersect(Ray ray, float &distance, XMFLOAT3 &baryCentric, XMFLOAT3 &norm) const {
        XMVECTOR xrd = XMLoadFloat3(&ray.direction);
        XMVECTOR xv0 = XMLoadFloat3(&v0);
        XMVECTOR xv1 = XMLoadFloat3(&v1);
        XMVECTOR xv2 = XMLoadFloat3(&v2);
        XMVECTOR xro = XMLoadFloat3(&ray.origin);
        //step1:
        //find the intersect point of plane and line
        XMVECTOR plane = XMPlaneFromPoints(xv0, xv1, xv2);
        XMVECTOR inter_point = XMPlaneIntersectLine(plane, xro, xro + xrd);
        //step2:
        //check if the intersect point is on the ray
        if (XMVector3Equal(inter_point, g_XMQNaN)) return false;
        if (XMVectorGetX(XMVector3Dot(xrd, inter_point - xro)) < 0) return false;
        //step3:
        //check if the intersect point is in the triangle
        XMVECTOR xd00 = XMVector3Dot(xv1 - xv0, xv1 - xv0);
        XMVECTOR xd01 = XMVector3Dot(xv1 - xv0, xv2 - xv0);
        XMVECTOR xd11 = XMVector3Dot(xv2 - xv0, xv2 - xv0);
        XMVECTOR xd20 = XMVector3Dot(inter_point - xv0, xv1 - xv0);
        XMVECTOR xd21 = XMVector3Dot(inter_point - xv0, xv2 - xv0);
        XMVECTOR xd = xd00 * xd11 - xd01 * xd01;
        float v = XMVectorGetX((xd11 * xd20 - xd01 * xd21) / xd);
        float w = XMVectorGetX((xd00 * xd21 - xd01 * xd20) / xd);
        float u = 1 - v - w;
        if (v < 0 || w < 0 || u < 0) return false;
        baryCentric.x = u;
        baryCentric.y = v;
        baryCentric.z = w;
        norm = n;
        distance = XMVectorGetX(XMVector3Length(inter_point - xro));
        return true;
    }

    // Returns barycentric coordinates of point p on the triangle

    // Returns the colour at point p on the triangle
    XMFLOAT3 get_colour_at(XMFLOAT3 b){
        if(m==NULL) return XMFLOAT3(1,0,1);

        return m->get_colour_at(t0.x * b.x + t1.x * b.y + t2.x * b.z, t0.y * b.x + t1.y * b.y + t2.y * b.z);
    }

};

#endif // TRIANGLE_H