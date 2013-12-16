#include "Spring.h"

Spring::Spring()
{
    //_particleA = nullptr;
    //_particleB = nullptr;
    _nLentght = 0;
}

Spring::Spring(Particle *particleA, Particle *particleB
               , float stifness, float nLength)
    : _particleA(particleA),
      _particleB(particleB)
{
    _nLentght = nLength;
    float dX = particleB->getPosition().getX() - particleA->getPosition().getX();
    float dY = particleB->getPosition().getY() - particleA->getPosition().getY();
    float dZ = particleB->getPosition().getZ() - particleA->getPosition().getZ();
    _nLentght = sqrt(dX * dX + dY * dY + dZ * dZ);
    _stiffness = stifness;
}

Spring::~Spring()
{
}

int Spring::Recalculate()
{
    Point3D<float> pA = _particleA->getPosition();
    Point3D<float> pB = _particleB->getPosition();
    Point3D<float> dist = pB;
    dist -= pA;

    float distLen = sqrt(dist.getX() * dist.getX() + dist.getY() * dist.getY()
                         + dist.getZ() * dist.getZ());

    float diff = _nLentght - distLen;

    float fX = diff * dist.getX() / distLen * _stiffness;
    float fY = diff * dist.getY() / distLen * _stiffness;
    float fZ = diff * dist.getZ() / distLen * _stiffness;

    _particleA->ApplyForce(-fX, -fY, -fZ);
    _particleB->ApplyForce( fX,  fY,  fZ);
    return 0;
}

void Spring::Draw()
{
     Point3D<float> p = this->_particleA->getPosition();
     glVertex3f(p.getX(), p.getY(), p.getZ());
     p = _particleB->getPosition();
     glVertex3f(p.getX(), p.getY(), p.getZ());
}

Particle *Spring::getParticleA()
{
    return _particleA;
}

Particle *Spring::getParticleB()
{
    return _particleB;
}
