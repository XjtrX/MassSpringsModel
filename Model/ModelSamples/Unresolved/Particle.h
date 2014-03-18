#ifndef PARTICLE_H
#define PARTICLE_H

#include "Model/Interfaces/DrawableObject.h"
#include "3DMath/ParticleState.h"

#include "Model/Interfaces/MovableObject.h"

class Particle: public MovableObject
{
public:
    Particle(const Particle& particle);
    Particle(const ParticleState& initialState
             , const float& massVolume, const float& borderRadius = 1, const int& st = 0);
    virtual ~Particle();

public:
    ParticleState _state;
    ParticleState _prevState;
    Point3D<float> _averageVelocity;
    Point3D<float> _approximateVelocity;
    Point3D<float> _appliedForce;
    float _massVolume;
    int _static;
    float _borderRadius;
    int _collided;

public:
    virtual void Draw();

    int isStatic();
    void setStatic(int st);
    float getBorderRadius();
    float getMassVolume();

    Point3D<float>& getPosition();

    virtual void Move(const float &timestep) = 0;
    virtual void ApplyForce(const float& fX, const float& fY, const float& fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void CalculateAverageVelocity(const float &timestep);
    virtual void Accelerate(const float &timestep);
//    virtual void Collide(const float &timestep);

    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep) = 0;
    virtual Point3D<float> getVelocity();

    virtual void ComputeFinalPosition(const float &timestep);
};

#endif // PARTICLE_H
