#ifndef MATERIAL_H
#define MATERIAL_H

#include "../lib/rand48/erand48.h"
#include "vector.h"
#include "ray.h"
#include "texture.h"

enum MaterialType { DIFF, SPEC, EMIT };


class Material {

private:
	MaterialType m_type;
	XMFLOAT3 m_colour;
	XMFLOAT3 m_emission;
    Texture m_texture;


public:
	Material(MaterialType t = DIFF, FXMVECTOR c = XMVectorSet(1, 1, 1, 0), FXMVECTOR e = XMVectorZero(), Texture tex = Texture());
	MaterialType get_type() const;
	XMFLOAT3 get_colour() const;
	XMFLOAT3 get_colour_at(float u, float v) const;
	XMFLOAT3 get_emission() const;
	Ray get_reflected_ray( const Ray &r, FXMVECTOR&p, const FXMVECTOR &n, unsigned short *Xi ) const;

};


#endif // MATERIAL_H