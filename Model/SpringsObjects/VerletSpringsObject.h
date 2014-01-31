#ifndef SPRINGSOBJECT_H
#define SPRINGSOBJECT_H

#include "Model/Interfaces/VerletObject.h"
#include "Model/ModelSamples/Spring.h"

#include <vector>
using namespace std;

class VerletSpringsObject: public VerletObject
{
public:
    VerletSpringsObject(int particlesCount, int springsCount);
    virtual ~VerletSpringsObject();
    void Draw();

    void RecalculateSprings();

    void ApplyForce(const float &fX, const float &fY, const float &fZ);
    void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
    void Accelerate(const float &timeStep);
    void Move();
    void Collide(int flag);
//protected:
public:
    int _particlesCount;
    int _springsCount;
    vector<Particle*> _particles;
    vector<Spring*> _springs;
};

#endif // SPRINGSOBJECT_H
