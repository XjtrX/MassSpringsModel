#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "3DMath/Point3D.h"

class MovableObject
{
public:
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ) = 0;
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ) = 0;
    virtual void CalculateAverageVelocity(const float& timestep) = 0;
    virtual void Accelerate(const float &timestep) = 0;
    virtual void Move(const float& timestep) = 0;
    virtual void Collide(const float& timestep) = 0;
    virtual void setVelocity(const Point3D<float>& newVelocity, const float& timestep) = 0;
    virtual void ComputeFinalPosition(const float& timestep) = 0;
    //virtual Point3D<float> getVelocity();
};

#endif // MOVABLEOBJECT_H
