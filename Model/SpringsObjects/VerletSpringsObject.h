#ifndef VERLETSPRINGSOBJECT_H
#define VERLETSPRINGSOBJECT_H

#include "Model/Interfaces/VerletObject.h"
#include "Model/SpringsObjects/SpringsObject.h"

class VerletSpringsObject: public SpringsObject//, public VerletObject
{
public:
    VerletSpringsObject(int particlesCount, int springsCount, int structuralSpringsCount, int clothTrianglesCount);
    virtual ~VerletSpringsObject();

    void Collide(int flag);

    virtual void Accelerate(const float &timestep);
    virtual void Move();
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);

    virtual void Iteration(float timeInterval);
};

#endif // VERLETSPRINGSOBJECT_H
