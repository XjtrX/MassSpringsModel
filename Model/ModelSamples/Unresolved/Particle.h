#ifndef PARTICLE_H
#define PARTICLE_H

#include "Model/Interfaces/DrawableObject.h"
#include "3DMath/ParticlePosition.h"

#include "Model/Interfaces/VerletObject.h"

class Particle: public VerletObject
{
public:
    Particle();
    Particle(const Particle& particle);
    Particle(const ParticlePosition& initialPosition
             , const float& massVolume, const float& borderRadius = 1, const int& st = 0);
    virtual ~Particle();

public:
    ParticlePosition _position;
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
    virtual void Accelerate(const float &timeStep);
    virtual void ApplyForce(const float& fX, const float& fY, const float& fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void Collide(int flag) = 0;

};

#endif // PARTICLE_H
