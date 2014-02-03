#include "VerletParticle.h"

VerletParticle::VerletParticle()
{
}

VerletParticle::VerletParticle(const ParticlePosition initialPosition
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

    ParticlePosition temp = _position;
    //_position.Plus(_position);
    _position += _position;
    //_position.Minus(_prevPosition);
    _position -= _prevPosition;
    //_position.Plus(_appliedForce);
    _prevPosition = temp;
    //_appliedForce.set(0, 0, 0);
}

Point3D<float>& VerletParticle::PrevPosition()
{
    return _prevPosition._position;
}

void VerletParticle::Collide(int)
{
}
