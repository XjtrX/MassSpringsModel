#ifndef SPRING_H
#define SPRING_H

#include "Particle.h"

#include <math.h>
using namespace std;
class Spring
{
private:
    Particle* _particleA;
    Particle* _particleB;
    float _nLentght;

public:
    Spring()
    {
        //_particleA = nullptr;
        //_particleB = nullptr;
        _nLentght = 0;
    }

    Spring(Particle* particleA, Particle* particleB, float nLength)
        :_particleA(particleA),
          _particleB(particleB)
    {
        _nLentght = nLength;
        float dX = particleB->getPosition().getX() - particleA->getPosition().getX();
        float dY = particleB->getPosition().getY() - particleA->getPosition().getY();
        float dZ = particleB->getPosition().getZ() - particleA->getPosition().getZ();
        _nLentght = sqrt(dX * dX + dY * dY + dZ * dZ);
    }

    int Recalculate()
    {
        Point3D<float> pA = _particleA->getPosition();
        Point3D<float> pB = _particleB->getPosition();
/*
        Point3D<float> dist = pB;
        dist.Minus(pA);

        float distLen = sqrt(dist.getX() * dist.getX() + dist.getY() * dist.getY()
                             + dist.getZ() * dist.getZ());

        float diff = _nLentght - distLen;

        float fX = diff * dist.getX() / distLen * 0.1;
        float fY = diff * dist.getY() / distLen * 0.1;
        float fZ = diff * dist.getZ() / distLen * 0.1;

        _particleA->ApplyForce(-fX, -fY, -fZ);
        _particleB->ApplyForce( fX,  fY,  fZ);
        return 0;
*/
        float dX = pB._x - pA._x;
        float dY = pB._y - pA._y;
        float dZ = pB._z - pA._z;

        float distLen = sqrt(dX * dX + dY * dY);
        float diff = _nLentght - distLen;

        float fX = dX * diff / distLen * 0.5;
        float fY = dY * diff / distLen * 0.5;

        _particleA->ApplyForce(-fX, -fY, 0);
        _particleB->ApplyForce( fX,  fY, 0);
        return 0;
    }

    Particle* getParticleA()
    {
        return _particleA;
    }

    Particle* getParticleB()
    {
        return _particleB;
    }

    ~Spring()
    {

    }
};

#endif // SPRING_H
