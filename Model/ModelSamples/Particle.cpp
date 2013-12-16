#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(Point3D<float> initialPosition, float massVolume, int st)
{
    _prevPosition = initialPosition;
    _position = initialPosition;
    _appliedForce.set(0, 0, 0);
    _massVolume = massVolume;
    _static = st;
}

Particle::~Particle()
{
}

void Particle::Move()
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

void Particle::Accelerate(float timeStep)
{
    float koeff = timeStep * timeStep / 2 / _massVolume;
    _position.PlusX(_appliedForce.getX() * koeff);
    _position.PlusY(_appliedForce.getY() * koeff);
    _position.PlusZ(_appliedForce.getZ() * koeff);
    _appliedForce.set(0, 0, 0);
}

Point3D<float> Particle::getPrevPosition()
{
    return _prevPosition;
}

Point3D<float> Particle::getPosition()
{
    return _position;
}

void Particle::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    _appliedForce.PlusX(fX);
    _appliedForce.PlusY(fY);
    _appliedForce.PlusZ(fZ);
}

void Particle::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    _appliedForce.PlusX(fX * _massVolume);
    _appliedForce.PlusY(fY * _massVolume);
    _appliedForce.PlusZ(fZ * _massVolume);
}

void Particle::Collusion()
{
}

int Particle::isStatic()
{
    return _static;
}

void Particle::setStatic(int st)
{
    _static = st;
}
