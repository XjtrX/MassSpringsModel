#ifndef VerletParticle_H
#define VerletParticle_H

#include "Model/ModelSamples/Unresolved/Particle.h"
#include "Model/Interfaces/VerletObject.h"

class VerletParticle: public Particle, public VerletObject
{
public:
    Point3D<float> _appliedForce;

    VerletParticle();
    VerletParticle(const ParticleState &initialState
                   , const float massVolume, const float borderRadius = 1
                   , const int st = 0);
    virtual ~VerletParticle();

    virtual void Move();
    virtual void Accelerate(const float &timestep);
    virtual void Collide(int flag);

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void CalculateAverageVelocity(const float &timestep);

    Point3D<float>& PrevPosition();
};

#endif // VerletParticle_H
