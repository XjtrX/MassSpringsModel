#ifndef VerletParticle_H
#define VerletParticle_H

#include "Model/ModelSamples/Particle.h"
#include "Model/Interfaces/VerletObject.h"

class VerletParticle: public Particle, public VerletObject
{
public:
//    Point3D<float> _appliedForce;

    VerletParticle(const ParticleState &initialState
                   , const float &massVolume, const float &borderRadius = 1
                   , const int &st = 0);
    virtual ~VerletParticle();

    virtual void Inertia(const float &timestep);
    virtual void Accelerate(const float &timestep);

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void CalculateAverageVelocity(const float &timestep);

    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual Point3D<float> getVelocity();

    virtual void ComputeFinalPosition(const float &timestep);
    virtual void ApplyCorrection(const float &timestep);

    Point3D<float>& PrevPosition();
};

#endif // VerletParticle_H
