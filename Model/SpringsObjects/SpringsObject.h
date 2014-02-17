#ifndef SPRINGSOBJECT_H
#define SPRINGSOBJECT_H

#include "Model/Interfaces/DrawableObject.h"
#include "Model/ModelSamples/Spring.h"
#include "Model/ModelSamples/Unresolved/Particle.h"
#include "Model/Interfaces/MovableObject.h"

#include <vector>
using namespace std;

class SpringsObject: public MovableObject, public DrawableObject
{
public:
    SpringsObject();
    virtual ~SpringsObject();

    SpringsObject(int particlesCount, int springsCount, int structuralSpringsCount);

    virtual void Draw();

    virtual void Iteration(float timeInterval) = 0;

    virtual void RecalculateSprings();

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
    virtual void Accelerate(const float &timeStep);
    virtual void Move();
    virtual void Collide(int flag);

public:
    int _particlesCount;
    int _springsCount;
    int _structuralSpringsCount;
    vector<Particle*> _particles;
    vector<Spring*> _springs;
    vector<Spring*> _structuralSprings;

};

#endif // SPRINGSOBJECT_H
