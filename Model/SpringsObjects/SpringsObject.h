#ifndef SPRINGSOBJECT_H
#define SPRINGSOBJECT_H

#include "Model/VerletObject.h"
#include "Model/ModelSamples/Spring.h"

#include <vector>
using namespace std;

class SpringsObject: public VerletObject
{
public:
    SpringsObject(int particlesCount, int springsCount);
    ~SpringsObject();
    void Draw();

    void RecalculateSprings();

    void ApplyForce(const float &fX, const float &fY, const float &fZ);
    void Accelerate(float timeStep);
    void Move();
    void Collusion();
//protected:
public:
    int _particlesCount;
    int _springsCount;
    vector<Particle> _particles;
    vector<Spring> _springs;
};

#endif // SPRINGSOBJECT_H
