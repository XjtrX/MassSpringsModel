#ifndef VerletParticle_H
#define VerletParticle_H

#include "Model/ModelSamples/Unresolved/Particle.h"
#include "Model/Interfaces/VerletObject.h"

class VerletParticle: public Particle//, public VerletObject
{
public:
    ParticlePosition _prevPosition;
    Point3D<float> _appliedForce;

    VerletParticle();
    VerletParticle(const ParticlePosition initialPosition
                   , const float massVolume, const float borderRadius = 1
                   , const int st = 0);
    virtual ~VerletParticle();

    virtual void Move();
    virtual void Collide(int flag);

    Point3D<float>& PrevPosition();

};

#endif // VerletParticle_H
