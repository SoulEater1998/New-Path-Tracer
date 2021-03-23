#ifndef CAMERA_H
#define CAMERA_H

#include "../lib/rand48/erand48.h"
#include "vector.h"
#include "ray.h"

class Camera {

private:
    int m_width;
    int m_height;
    Vec m_position;
    Vec m_direction;
    Vec m_x_direction;
    Vec m_y_direction;

public:
    Camera(Vec position, Vec target, int width, int height);
    int get_width();
    int get_height();
    Ray get_ray(int x, int y, bool jitter, unsigned short *Xi);

};

#endif //CAMERA_H