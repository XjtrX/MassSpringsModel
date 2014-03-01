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
    /*
    //_position.Plus(_position);
    _position += _position;
    //_position.Minus(_prevPosition);
    _position -= _prevPosition;
    //_position.Plus(_appliedForce);
    _prevPosition = temp;
    //_appliedForce.set(0, 0, 0);
    */
//    /*
    float coeff = 0.02;
    _position += _position;
    _position *= (1 - coeff / 2);
    _prevPosition *= (1 - coeff);
    _position -= _prevPosition;
    _prevPosition = temp;
    //    */
}

void VerletParticle::Accelerate(const float &timestep)
{
    Particle::Accelerate(timestep);
}

Point3D<float>& VerletParticle::PrevPosition()
{
    return _prevPosition._position;
}

void VerletParticle::Collide(int)
{
}

void VerletParticle::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    Particle::ApplyForce(fX, fY, fZ);
}

void VerletParticle::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    Particle::ApplyAcceleration(aX, aY, aZ);
}

void VerletParticle::CalculateAverageVelocity(const float &timestep)
{
    Particle::CalculateAverageVelocity(timestep);
}
