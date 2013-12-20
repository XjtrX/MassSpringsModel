#ifndef PARTICLE_H
#define PARTICLE_H

#include "Model/Interfaces/VerletObject.h"
#include "Model/Interfaces/DrawableObject.h"

#include "3DMath/Point3D.h"
class Particle: public VerletObject, public DrawableObject
{
public:
    Point3D<float> _prevPosition;
    Point3D<float> _position;
    Point3D<float> _appliedForce;
    float _massVolume;
    int _static;
    float _borderRadius;

    Particle();
    Particle(Point3D<float> initialPosition, float massVolume, float borderRadius = 1
            , int st = 0);
    virtual ~Particle();

    void Move();
    void Accelerate(const float &timeStep);
    Point3D<float>& PrevPosition();
    Point3D<float>& Position();
    void ApplyForce(const float& fX, const float& fY, const float& fZ);
    void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
    void Collide(int flag);

    void Draw();

    int isStatic();

    void setStatic(int st);

    float getBorderRadius();

    float getMassVolume();
};

#endif // PARTICLE_H
