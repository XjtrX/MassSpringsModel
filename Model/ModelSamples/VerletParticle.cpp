#include "VerletParticle.h"

VerletParticle::VerletParticle()
{
}

VerletParticle::VerletParticle(const Point3D<float> initialPosition
                               , const float massVolume, const float borderRadius
                               , const int st)
    : Particle(initialPosition, massVolume, borderRadius, st)
{
    _prevPosition = initialPosition;
    _appliedForce.set(0, 0, 0);
}

VerletParticle::~VerletParticle()
{
}

void VerletParticle::Move()
{
    if (_static)
    {
        _position = _prevPosition;
        _appliedForce.set(0, 0, 0);
        return;
    }

    Point3D<float> temp = _position;
    //_position.Plus(_position);
    _position += _position;
    //_position.Minus(_prevPosition);
    _position -= _prevPosition;
    //_position.Plus(_appliedForce);
    _prevPosition = temp;
    //_appliedForce.set(0, 0, 0);
}

void VerletParticle::Accelerate(const float &timeStep)
{
    float koeff = timeStep * timeStep / 2 / _massVolume;
    _position.PlusX(_appliedForce.getX() * koeff);
    _position.PlusY(_appliedForce.getY() * koeff);
    _position.PlusZ(_appliedForce.getZ() * koeff);
    _appliedForce.set(0, 0, 0);
}

Point3D<float>& VerletParticle::PrevPosition()
{
    return _prevPosition;
}

void VerletParticle::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    _appliedForce.PlusX(fX);
    _appliedForce.PlusY(fY);
    _appliedForce.PlusZ(fZ);
}

void VerletParticle::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    _appliedForce.PlusX(aX * _massVolume);
    _appliedForce.PlusY(aY * _massVolume);
    _appliedForce.PlusZ(aZ * _massVolume);
}

void VerletParticle::Collide(int flag)
{
}
