#ifndef KDTREE_H
#define KDTREE_H

#include <vector>

#include "vector.h"
#include "ray.h"
#include "triangle.h"

struct SAHNode
{
    size_t index;
    AABBox triBox;

    SAHNode(size_t i, AABBox b) {
        index = i;
        triBox = b;
    }
};

struct BucketInfo {
    int count = 0;
    AABBox bounds;
};

class KDNode {
public:
    AABBox box;
    KDNode* left;
    KDNode* right;
    std::vector<Triangle*> triangles;
    bool leaf;
    KDNode(){};
    KDNode(AABBox b, std::vector<Triangle*> t, std::vector<SAHNode*> s, size_t start, size_t end) {
        box = b;
        left = NULL;
        right = NULL;
        leaf = true;
        triangles = std::vector<Triangle*>();
        for (size_t i = start; i < end; ++i) {
            triangles.push_back(t[s[i]->index]);
        }
    }
    KDNode(AABBox b, KDNode* l, KDNode* r, std::vector<Triangle*> t, bool lf) {
        box = b;
        left = l;
        right = r;
        triangles = t;
        leaf = lf;
    }
    KDNode* build(std::vector<Triangle*> &tris, int depth);
    //KDNode* buildSAH(std::vector<SAHNode*>& sahs, std::vector<Triangle*>& tris, size_t start, size_t end);
    KDNode* build(std::vector<Triangle*>& tris);
    bool hit (KDNode* node, const Ray &ray, double &t, double &tmin, Vec &normal, Vec &c);
};

#endif // KDTREE_H