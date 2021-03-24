#ifndef AABBOX_H
#define AABBOX_H

#include <cfloat>
#include <algorithm>

#include "vector.h"
#include "ray.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;
// Axis-aligned bounding box
struct AABBox {
    XMFLOAT3 bl;     // Bottom left (min)
    XMFLOAT3 tr;     // Top right   (max)

    AABBox (XMFLOAT3 bl_=XMFLOAT3(), XMFLOAT3 tr_=XMFLOAT3()){
        bl=bl_, tr=tr_;
    }

    // Expand to fit box
    void expand(const AABBox &box) {
        if (box.bl.x < bl.x) bl.x = box.bl.x ;
        if (box.bl.y < bl.y) bl.y = box.bl.y;
        if (box.bl.z < bl.z) bl.z = box.bl.z;

        if (box.tr.x > tr.x) tr.x = box.tr.x;
        if (box.tr.y > tr.y) tr.y = box.tr.y;
        if (box.tr.z > tr.z) tr.z = box.tr.z ;
    }

    // Expand to fit point
    void expand(const XMFLOAT3 &vec) {
        if (vec.x < bl.x) bl.x = vec.x ;
        if (vec.y < bl.y) bl.y = vec.y;
        if (vec.z < bl.z) bl.z = vec.z;
    }

    // Returns longest axis: 0, 1, 2 for x, y, z respectively
    int get_longest_axis() {
        XMFLOAT3 diff(tr.x - bl.x, tr.y - bl.y, tr.z - bl.z);
        if (diff.x > diff.y && diff.x > diff.z) return 0;
        if (diff.y > diff.x && diff.y > diff.z) return 1;
        return 2;
    }

    // Check if ray intersects with box. Returns true/false and stores distance in t
    bool intersection(const Ray &r, float &t) {
        float tx1 = (bl.x - r.origin.x)*r.direction_inv.x;
        float tx2 = (tr.x - r.origin.x)*r.direction_inv.x;

        float tmin = min(tx1, tx2);
        float tmax = max(tx1, tx2);

        float ty1 = (bl.y - r.origin.y)*r.direction_inv.y;
        float ty2 = (tr.y - r.origin.y)*r.direction_inv.y;

        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));

        float tz1 = (bl.z - r.origin.z)*r.direction_inv.z;
        float tz2 = (tr.z - r.origin.z)*r.direction_inv.z;

        tmin = max(tmin, min(tz1, tz2));
        tmax = min(tmax, max(tz1, tz2));
        t = tmin;

        return tmax >= tmin;
    }
};

#endif // AABBOX_H