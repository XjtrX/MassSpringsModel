#ifndef VERLETSPRINGSOBJECT_H
#define VERLETSPRINGSOBJECT_H

#include "Model/Interfaces/VerletObject.h"
#include "Model/SpringsObjects/SpringsObject.h"

class VerletSpringsObject: public SpringsObject, public VerletObject
{
public:
    VerletSpringsObject(const int &cols, const int &rows, const float &width, const float &height
                  , const float &massVolume, const float &stiffnes, const float &thickness
                  , const Point3D<float> &rotation, const Point3D<float> &translation
                  , const int &withBendSprings);
    virtual ~VerletSpringsObject();

    virtual void Collide(const float &timestep);

    virtual void Accelerate(const float &timestep);
    virtual void Move(const float &timestep);
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual Point3D<float> getVelocity();

    virtual void CalculateAverageVelocity(const float &timestep);

    virtual void ComputeFinalPosition(const float &timestep);

    virtual void ResolveCollisions(const float &timestep);

    virtual void Iteration(float timeInterval);
};

#endif // VERLETSPRINGSOBJECT_H
