#include "Spring.h"

Spring::Spring()
{
    //_VerletParticleA = nullptr;
    //_VerletParticleB = nullptr;
    _nLentght = 0;
}

Spring::Spring(Particle *particleA, Particle *particleB, const float stifness
               , const float nLength, const int type)
    : _particleA(particleA), _particleB(particleB), _type(type)
{
    _nLentght = nLength;
    float dX = _particleB->getPosition().getX() - _particleA->getPosition().getX();
    float dY = _particleB->getPosition().getY() - _particleA->getPosition().getY();
    float dZ = _particleB->getPosition().getZ() - _particleA->getPosition().getZ();
    _nLentght = sqrt(dX * dX + dY * dY + dZ * dZ);
    _stiffness = stifness;
    _highlighted = 0;
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

    float distLen = sqrt(dist.getSquaredLength());

    float diff = _nLentght - distLen;

    float fX = diff * dist.getX() / distLen * _stiffness;
    float fY = diff * dist.getY() / distLen * _stiffness;
    float fZ = diff * dist.getZ() / distLen * _stiffness;

    _particleA->ApplyForce(-fX, -fY, -fZ);
    _particleB->ApplyForce( fX,  fY,  fZ);
    return 0;
}

#include <iostream>
void Spring::Draw(const int &flushColor)
{
    if (this->_highlighted)
    {
        glColor3f(1, 0, 0);
        if (flushColor)
        {
            this->_highlighted = 0;
        }
    }
    Point3D<float> p = this->_particleA->getPosition();
    glVertex3f(p.getX(), p.getY(), p.getZ());
    p = _particleB->getPosition();
    glVertex3f(p.getX(), p.getY(), p.getZ());
    glColor3f(1, 0.6, 0);
}

Particle *Spring::getParticleA()
{
    return _particleA;
}

Particle *Spring::getParticleB()
{
    return _particleB;
}
