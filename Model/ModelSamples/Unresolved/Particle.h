#ifndef PARTICLE_H
#define PARTICLE_H

#include "Model/Interfaces/DrawableObject.h"
//#include "3DMath/ParticlePosition.h"

#include "Model/Interfaces/MovableObject.h"

class Particle: public MovableObject
{
public:
    Particle();
    Particle(const Particle& particle);
    Particle(const Point3D<float>& initialPosition
             , const float& massVolume, const float& borderRadius = 1, const int& st = 0);
    virtual ~Particle();

public:
    Point3D<float> _position;
    Point3D<float> _prevPosition;
    Point3D<float> _velocity;
    Point3D<float> _prevVelocity;
    Point3D<float> _averageVelocity;
    Point3D<float> _appliedForce;
    float _massVolume;
    int _static;
    float _borderRadius;

public:
    virtual void Draw();

    int isStatic();
    void setStatic(int st);
    float getBorderRadius();
    float getMassVolume();

    Point3D<float>& getPosition();

    virtual void Move() = 0;
    virtual void ApplyForce(const float& fX, const float& fY, const float& fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void CalculateAverageVelocity(const float &timestep);
    virtual void Accelerate(const float &timestep);
    virtual void Collide(int flag);
};

#endif // PARTICLE_H
