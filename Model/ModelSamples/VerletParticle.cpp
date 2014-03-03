#include "VerletParticle.h"

VerletParticle::VerletParticle()
{
}

VerletParticle::VerletParticle(const ParticleState &initialState
                               , const float massVolume, const float borderRadius, const int st)
    : Particle(initialState, massVolume, borderRadius, st)
{
}

VerletParticle::~VerletParticle()
{
}

void VerletParticle::Move()
{
    if (_static)
    {
        _state._position = _prevState._position;
        _appliedForce.set(0, 0, 0);
        return;
    }

    ParticleState tempState = _state;
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
    _state._position += _state._position;
    _state._position *= (1 - coeff / 2);
    _prevState._position *= (1 - coeff);
    _state._position -= _prevState._position;
    _prevState = tempState;
    //    */
}

void VerletParticle::Accelerate(const float &timestep)
{
    Particle::Accelerate(timestep);
}

Point3D<float>& VerletParticle::PrevPosition()
{
    return _prevState._position;
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
