#ifndef VERLETSPRINGSOBJECT_H
#define VERLETSPRINGSOBJECT_H

#include "Model/Interfaces/VerletObject.h"
#include "Model/SpringsObjects/SpringsObject.h"

class VerletSpringsObject: public SpringsObject//, public VerletObject
{
public:
    VerletSpringsObject(const int& particlesCount, const int& springsCount, const int& structuralSpringsCount, const int& clothTrianglesCount, const float& thickness);
    virtual ~VerletSpringsObject();

    void Collide(int flag);

    virtual void Accelerate(const float &timestep);
    virtual void Move(const float &timestep);
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
//    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);

    virtual void Iteration(float timeInterval);
};

#endif // VERLETSPRINGSOBJECT_H
