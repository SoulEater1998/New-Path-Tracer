#ifndef TEXTURE_H
#define TEXTURE_H
#include <vector>
#include "vector.h"

class Texture {
private:
    unsigned width;
    unsigned height;
    bool loaded = false;
    std::vector<unsigned char> image;
public:
    Texture(const char* filename);
    Texture(){};
    XMFLOAT3 get_pixel(unsigned x, unsigned y) const;
    XMFLOAT3 get_pixel(float u, float v) const;
    bool is_loaded() const;
};

#endif // TEXTURE_H