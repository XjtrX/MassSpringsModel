#ifndef EULERSPRINGSOBJECT_H
#define EULERSPRINGSOBJECT_H

#include "Model/SpringsObjects/SpringsObject.h"
#include "Model/Interfaces/EulerObject.h"
#include "Model/ModelSamples/EulerParticle.h"

class EulerSpringsObject: public SpringsObject, public EulerObject
{
public:
    EulerSpringsObject(const int &cols, const int &rows, const float &width, const float &height
                       , const float &massVolume, const float &stiffnes, const float &thickness
                       , const Point3D<float> &rotation, const Point3D<float> &translation
                       , const int &withBendSprings);

    virtual ~EulerSpringsObject();

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void CalculateAverageVelocity(const float &timestep);
    virtual void Accelerate(const float &timestep);
    virtual void Move(const float &timestep);
    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual void ComputeFinalPosition(const float &timestep);

    virtual void Iteration(float timeInterval);
};

#endif // EULERSPRINGSOBJECT_H
