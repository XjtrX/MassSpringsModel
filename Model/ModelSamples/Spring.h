#ifndef SPRING_H
#define SPRING_H

#include "Model/Interfaces/ElasticObject.h"
#include "Model/ModelSamples/Particle.h"

#include <math.h>
using namespace std;
class Spring: public ElasticObject
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

    Particle* getParticleA();
    Particle* getParticleB();

};

#endif // SPRING_H
