#include "ray.h"
#include "camera.h"

Camera::Camera(FXMVECTOR position, FXMVECTOR target, int width, int height) {
    m_width = width;
    m_height = height;
    XMStoreFloat3(&m_position, position);

    XMVECTOR xtar = XMLoadFloat3(&target);
    XMVECTOR xmp = XMLoadFloat3(&m_position);
    XMVECTOR xmd = XMVector3Normalize(xtar - xmp);
    XMVECTOR xmxd = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), -xmd));
    XMVECTOR xmyd = XMVector3Normalize(XMVector3Cross(xmxd, xmd));
    XMStoreFloat3(&m_direction, xmd);
    XMStoreFloat3(&m_x_direction, xmxd);
    XMStoreFloat3(&m_y_direction, xmyd);
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
    XMVECTOR xmp = XMLoadFloat3(&m_position);
    XMVECTOR xmd = XMLoadFloat3(&m_direction);
    XMVECTOR xmxd = XMLoadFloat3(&m_x_direction);
    XMVECTOR xmyd = XMLoadFloat3(&m_y_direction);
    XMVECTOR xp = xmp + xmd * 2 + xmxd * ((2.0f * x - m_width + x_jitter) / m_height) + xmyd * ((2.0f * y - m_width + y_jitter) / m_height);

    Vec pixel = m_position + m_direction*2;
    pixel = pixel + m_x_direction * ((2.0f * x - m_width + x_jitter) / m_height);
    pixel = pixel + m_y_direction * ((2.0f * y - m_width + y_jitter) / m_height);

    return Ray(m_position, (pixel-m_position).norm());
}