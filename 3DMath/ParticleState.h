#ifndef POINTSTATE_H
#define POINTSTATE_H

#include "ParticlePosition.h"

class ParticleState: public ParticlePosition
{
public:
    Point3D<float> _velocity;

    ParticleState();
    virtual ~ParticleState();

    ParticleState(const ParticleState& ps);
    ParticleState(const Point3D<float>& position, const Point3D<float>& velocity);

    virtual ParticleState& operator +=(const ParticleState& other);
    virtual ParticleState& operator *=(const float& coeff);
};

#endif // POINTSTATE_H
