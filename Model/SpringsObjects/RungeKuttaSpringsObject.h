#ifndef RUNGEKUTTASPRINGSOBJECT_H
#define RUNGEKUTTASPRINGSOBJECT_H

#include "Model/Interfaces/RungeKuttaObject.h"
#include "Model/SpringsObjects/SpringsObject.h"

#include "Model/ModelSamples/RungeKuttaParticle.h"

class RungeKuttaSpringsObject: public SpringsObject, public RungeKuttaObject
{
public:
    vector<RungeKuttaParticle*> _rKParticles;

public:
    RungeKuttaSpringsObject(const int &cols, const int &rows, const float &width, const float &height
                  , const float &massVolume, const float &stiffnes, const float &thickness
                  , const Point3D<float> &rotation, const Point3D<float> &translation
                  , const int &withBendSprings);
    virtual ~RungeKuttaSpringsObject();

public:
    virtual void ComputeK1(float timestep);
    virtual void ComputeK2(float timestep);
    virtual void ComputeK3(float timestep);
    virtual void ComputeK4(float timestep);

    virtual void Iteration(float timeInterval);

    virtual void Move(const float &timestep);
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void Accelerate(const float &timestep);
    virtual void CalculateAverageVelocity(const float &timestep);

    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual Point3D<float> getVelocity();

    virtual void ComputeFinalPosition(const float &timestep);

    virtual void Collide(const float &timestep);
    virtual void ResolveCollisions(const float &timestep);

    virtual void MoveEachOther(const float& timestep);

    void RecalculateConnectionsAffort();
};

#endif // RUNGEKUTTASPRINGSOBJECT_H
