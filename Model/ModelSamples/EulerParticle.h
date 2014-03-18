#ifndef EULERPARTICLE_H
#define EULERPARTICLE_H

#include "Model/ModelSamples/Unresolved/Particle.h"
#include "Model/Interfaces/EulerObject.h"

class EulerParticle: public Particle, public EulerObject
{
public:
    EulerParticle(const ParticleState &initialState
                  , const float &massVolume, const float &borderRadius = 0, const int &st = 0);

    virtual ~EulerParticle();

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void CalculateAverageVelocity(const float &timestep);
    virtual void Accelerate(const float &timestep);
    virtual void Move(const float &timestep);
    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual void ComputeFinalPosition(const float &timestep);
};

#endif // EULERPARTICLE_H
