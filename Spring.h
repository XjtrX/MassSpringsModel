#ifndef SPRING_H
#define SPRING_H

#include "Particle.h"
class Spring
{
private:
    Particle* _particleA;
    Particle* _particleB;

public:
    Spring():_particleA(NULL), _particleB(NULL)
    {

    }

    Spring(Particle* particleA, Particle* particleB, QString str)
        :_particleA(particleA),
          _particleB(particleB)
    {
        _particleA->_str += str;
        _particleB->_str += str;
    }

    ~Spring()
    {

    }
};

#endif // SPRING_H
