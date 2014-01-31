#ifndef VerletParticle_H
#define VerletParticle_H

#include "Model/ModelSamples/Particle.h"
#include "Model/Interfaces/VerletObject.h"

#include "3DMath/Point3D.h"
class VerletParticle: public Particle, public VerletObject
{
public:
    Point3D<float> _prevPosition;
    Point3D<float> _appliedForce;

    VerletParticle();
    VerletParticle(const Point3D<float> initialPosition
                   , const float massVolume, const float borderRadius = 1
                   , const int st = 0);
    virtual ~VerletParticle();

    virtual void Move();
    virtual void Accelerate(const float &timeStep);
    virtual void ApplyForce(const float& fX, const float& fY, const float& fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void Collide(int flag);

    Point3D<float>& PrevPosition();

};

#endif // VerletParticle_H
