#ifndef PARTICLEPOSITION_H
#define PARTICLEPOSITION_H

#include "Point3D.h"
#include <glm/glm/glm.hpp>

class ParticlePosition
{
public:
    Point3D<float> _position;
public:
    ParticlePosition();
    ParticlePosition(const Point3D<float>& p);
    ParticlePosition(const ParticlePosition& other);
    virtual ~ParticlePosition();

    virtual ParticlePosition& operator +=(const ParticlePosition& other);
    virtual ParticlePosition& operator -=(const ParticlePosition& other);

    virtual ParticlePosition& operator *=(const float& coeff);
};

#endif // PARTICLEPOSITION_H
