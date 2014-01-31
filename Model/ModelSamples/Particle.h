#ifndef PARTICLE_H
#define PARTICLE_H

#include "Model/Interfaces/DrawableObject.h"
#include "3DMath/Point3D.h"

class Particle
{
public:
    Particle();
    Particle(const Particle& particle);
    Particle(const Point3D<float>& initialPosition
             , const float& massVolume, const float& borderRadius = 1, const int& st = 0);
    virtual ~Particle();

public:
    Point3D<float> _position;
    float _massVolume;
    int _static;
    float _borderRadius;

public:
    virtual void Draw();

    Point3D<float>& Position();

    int isStatic();
    void setStatic(int st);
    float getBorderRadius();
    float getMassVolume();

    virtual void Move() = 0;
    virtual void Accelerate(const float &timeStep) = 0;
    virtual void ApplyForce(const float& fX, const float& fY, const float& fZ) = 0;
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ) = 0;
    virtual void Collide(int flag) = 0;

};

#endif // PARTICLE_H
