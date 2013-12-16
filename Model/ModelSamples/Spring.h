#ifndef SPRING_H
#define SPRING_H

#include "Model/Interfaces/ElasticObject.h"
#include "Model/Interfaces/DrawableObject.h"

#include "Model/ModelSamples/Particle.h"

#include <math.h>
using namespace std;
class Spring: public ElasticObject, public DrawableObject
{
private:
    Particle* _particleA;
    Particle* _particleB;
    float _nLentght;
    float _stiffness;
//    float _maxLength;

public:
    Spring();
    Spring(Particle* particleA, Particle* particleB
           , float stifness, float nLength = 0);
    ~Spring();

    int Recalculate();

    void Draw();

    Particle* getParticleA();
    Particle* getParticleB();

};

#endif // SPRING_H
