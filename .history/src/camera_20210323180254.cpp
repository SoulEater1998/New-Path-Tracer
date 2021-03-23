#include "ray.h"
#include "camera.h"

Camera::Camera(Vec position, Vec target, int width, int height) {
    m_width = width;
    m_height = height;

    m_position = position;
    m_direction = (target - m_position).norm();
    m_x_direction = Vec(0, 0, 1).cross(m_direction * -1).norm();
    m_y_direction = m_x_direction.cross(m_direction).norm();
}

int Camera::get_width() { return m_width; }
int Camera::get_height() { return m_height; }

// Returns ray from camera origin through pixel at x,y
Ray Camera::get_ray(int x, int y, bool jitter, unsigned short *Xi) {

    float x_jitter;
    float y_jitter;

    // If jitter == true, jitter point for anti-aliasing
    if (jitter) {
        x_jitter = erand48(Xi) * 2 - 1;
        y_jitter = erand48(Xi) * 2 - 1;
    }
    else {
        x_jitter = 0;
        y_jitter = 0;
    }
    XMVECTOR mp = XMLoadFloat3(&m_position);
    XMVECTOR md = XMLoadFloat3(&m_direction);
    Vec pixel = m_position + m_direction*2;
    pixel = pixel + m_x_direction * ((2.0f * x - m_width + x_jitter) / m_height);
    pixel = pixel + m_y_direction * ((2.0f * y - m_width + y_jitter) / m_height);

    return Ray(m_position, (pixel-m_position).norm());
}