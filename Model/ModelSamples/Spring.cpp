#include "Spring.h"

Spring::Spring()
{
    //_VerletParticleA = nullptr;
    //_VerletParticleB = nullptr;
    _nLentght = 0;
}

Spring::Spring(Particle *particleA, Particle *particleB
               , const float stifness, const float nLength)
    : _particleA(particleA), _particleB(particleB)
{
    _nLentght = nLength;
    float dX = _particleB->Position().getX() - _particleA->Position().getX();
    float dY = _particleB->Position().getY() - _particleA->Position().getY();
    float dZ = _particleB->Position().getZ() - _particleA->Position().getZ();
    _nLentght = sqrt(dX * dX + dY * dY + dZ * dZ);
    _stiffness = stifness;
}

Spring::~Spring()
{
}

int Spring::Recalculate()
{
    Point3D<float> pA = _particleA->Position();
    Point3D<float> pB = _particleB->Position();
    Point3D<float> dist = pB;
    dist -= pA;

    float distLen = sqrt(dist.getSquaredLength());

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
     Point3D<float> p = this->_particleA->Position();
     glVertex3f(p.getX(), p.getY(), p.getZ());
     p = _particleB->Position();
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
