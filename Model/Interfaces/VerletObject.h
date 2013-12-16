#ifndef VERLETOBJECT_H
#define VERLETOBJECT_H

class VerletObject
{
public:
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ) = 0;
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ) = 0;
    virtual void Accelerate(float timeStep) = 0;
    virtual void Move() = 0;
    virtual void Collusion() = 0;
};

#endif // VERLETOBJECT_H
