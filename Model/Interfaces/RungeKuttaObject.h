#ifndef RUNGEKUTTAOBJECT_H
#define RUNGEKUTTAOBJECT_H

#include "MovableObject.h"
#include "3DMath/ParticleState.h"

class RungeKuttaObject: public MovableObject
{
    //virtual ParticleState RKTransformation(ParticleState& particleState, float dt) = 0;
    virtual void ComputeK1(float timestep) = 0;
    virtual void ComputeK2(float timestep) = 0;
    virtual void ComputeK3(float timestep) = 0;
    virtual void ComputeK4(float timestep) = 0;
};

#endif // RUNGEKUTTAOBJECT_H
