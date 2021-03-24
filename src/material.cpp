#include <stdlib.h>

#include "vector.h"
#include "ray.h"
#include "material.h"

Material::Material(MaterialType t, FXMVECTOR c, FXMVECTOR e, Texture tex) {
	m_type=t;
    XMStoreFloat3(&m_colour, c);
    XMStoreFloat3(&m_emission, e);
    m_texture = tex;
}

MaterialType Material::get_type() const { return m_type; }
XMFLOAT3 Material::get_colour() const { return m_colour; }

// Get colour at UV coordinates u,v
XMFLOAT3 Material::get_colour_at(float u, float v) const {
    if (m_texture.is_loaded())
        return m_texture.get_pixel(u, v);

    return m_colour;
}
XMFLOAT3 Material::get_emission() const { return m_emission; }

Ray Material::get_reflected_ray(const Ray &r, FXMVECTOR &p, const FXMVECTOR &n,	unsigned short *Xi) const {
	// Ideal specular reflection
    XMVECTOR xrd = XMLoadFloat3(&r.direction);
	if (m_type == SPEC) {
        float roughness = 0.8;
        XMVECTOR reflected = xrd - n * 2 * XMVector3Dot(n, xrd);
        XMVECTOR jitter = XMVectorSet((erand48(Xi) - 0.5) * roughness, (erand48(Xi) - 0.5) * roughness, (erand48(Xi) - 0.5) * roughness, 0.0f);
        reflected = XMVector3Normalize(reflected + jitter);

        return Ray(p, reflected);
		//return Ray(p, r.direction - n * 2 * n.dot(r.direction));
	}
	// Ideal diffuse reflection
	if (m_type == DIFF) {
		Vec nl=n.dot(r.direction)<0?n:n*-1;
		float r1=2*M_PI*erand48(Xi), r2=erand48(Xi), r2s=sqrt(r2);
        Vec w = nl, u = ((fabs(w.x) > .1 ? Vec(0, 1) : Vec(1)) % w).norm(), v = w % u;
        Vec d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();

        return Ray(p, d);
	}
}