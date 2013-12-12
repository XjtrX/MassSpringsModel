#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(Point3D<float> initialPosition, int st)
{
    _prevPosition = initialPosition;
    _position = initialPosition;
    _appliedForce.set(0, 0, 0);
    _static = st;
}

Particle::~Particle()
{
}

void Particle::Move()
{
    if (_static)
    {
        _appliedForce.set(0, 0, 0);
        return;
    }

    Point3D<float> temp = _position;
    _position.Plus(_position);
    _position.Minus(_prevPosition);
    //_position.Plus(_appliedForce);
    _prevPosition = temp;
    //_appliedForce.set(0, 0, 0);
}

void Particle::Accelerate(float timeStep)
{
    _position.PlusX(_appliedForce.getX() * timeStep * timeStep / 2);
    _position.PlusY(_appliedForce.getY() * timeStep * timeStep / 2);
    _position.PlusZ(_appliedForce.getZ() * timeStep * timeStep / 2);
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

int Particle::isStatic()
{
    return _static;
}

void Particle::setStatic(int st)
{
    _static = st;
}
