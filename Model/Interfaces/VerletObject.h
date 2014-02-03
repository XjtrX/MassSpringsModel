#ifndef VERLETOBJECT_H
#define VERLETOBJECT_H

#include "MovableObject.h"

class VerletObject: public MovableObject
{
public:
    virtual void Accelerate(const float &timeStep) = 0;
    //virtual void Collide(int flag) = 0;
};

#endif // VERLETOBJECT_H
