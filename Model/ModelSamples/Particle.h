#ifndef PARTICLE_H
#define PARTICLE_H

#include "Model/Interfaces/VerletObject.h"

#include "3DMath/Point3D.h"
class Particle: public VerletObject
{
public:
    Point3D<float> _prevPosition;
    Point3D<float> _position;
    Point3D<float> _appliedForce;
    //float _massVolume;
    int _static;

    Particle();
    Particle(Point3D<float> initialPosition, int st = 0);
    ~Particle();

    void Move();
    void Accelerate(float timeStep);
    Point3D<float> getPrevPosition();
    Point3D<float> getPosition();
    void ApplyForce(const float& fX, const float& fY, const float& fZ);
    void Collusion();

    int isStatic();

    void setStatic(int st);
};

#endif // PARTICLE_H
