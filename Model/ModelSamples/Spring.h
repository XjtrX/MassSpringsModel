#ifndef SPRING_H
#define SPRING_H

#include "Model/Interfaces/ElasticObject.h"
#include "Model/Interfaces/DrawableObject.h"

#include "Model/ModelSamples/Unresolved/Particle.h"

#include <math.h>
using namespace std;

#define structural 0
#define shear 1
#define bend 2

class Spring: public ElasticObject, public DrawableObject
{
public:
    Particle* _particleA;
    Particle* _particleB;
public:
    float _nLentght;
    float _stiffness;
//    float _maxLength;
    int _type;
    int _highlighted;

public:
    Spring();
    Spring(Particle *particleA, Particle *particleB
           , const float stifness, const float nLength = 0, const int type = structural);
    virtual ~Spring();

    int Recalculate();

    void Draw(const int &flushColor);

    Particle* getParticleA();
    Particle* getParticleB();
};

#endif // SPRING_H
