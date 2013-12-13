#ifndef VERLETOBJECT_H
#define VERLETOBJECT_H

class VerletObject
{
public:
    void ApplyForce(const float &fX, const float &fY, const float &fZ);
    void Accelerate(float timeStep);
    void Move();
    void Collusion();
};

#endif // VERLETOBJECT_H
