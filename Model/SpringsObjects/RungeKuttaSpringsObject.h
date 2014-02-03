#ifndef RUNGEKUTTASPRINGSOBJECT_H
#define RUNGEKUTTASPRINGSOBJECT_H

#include "Model/Interfaces/RungeKuttaObject.h"
#include "Model/SpringsObjects/SpringsObject.h"

class RungeKuttaSpringsObject: public SpringsObject, public RungeKuttaObject
{
public:
    RungeKuttaSpringsObject(int particlesCount, int springsCount);
    virtual ~RungeKuttaSpringsObject();

public:
    virtual void ComputeK1(float timestep);
    virtual void ComputeK2(float timestep);
    virtual void ComputeK3(float timestep);
    virtual void ComputeK4(float timestep);

    virtual void Iteration(float timeInterval);

    virtual void Move();
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
};

#endif // RUNGEKUTTASPRINGSOBJECT_H
