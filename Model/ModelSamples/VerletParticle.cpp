#include "VerletParticle.h"

VerletParticle::VerletParticle(const ParticleState &initialState
                               , const float &massVolume, const float &borderRadius, const int &st)
    : Particle(initialState, massVolume, borderRadius, st)
{
}

VerletParticle::~VerletParticle()
{
}

void VerletParticle::Inertia(const float &timestep)
{
    if (_static)
    {
        _state._position = _prevState._position;
        _state._velocity.set(0, 0, 0);
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
    float coeff = 0.002;
    _state._position += _state._position;
    _state._position *= (1 - coeff / 2);
    _prevState._position *= (1 - coeff);
    _state._position -= _prevState._position;
    _state._velocity = (_state._position - _prevState._position) / timestep;
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

void VerletParticle::setVelocity(const Point3D<float> &newVelocity, const float &timestep)
{
    if (!_static)
    {
        _prevState._position = newVelocity;
        _prevState._position *= -timestep;
        _prevState._position += _state._position;
        _state._velocity = newVelocity;
    }
}

Point3D<float> VerletParticle::getVelocity()
{
    return Particle::getVelocity();
}

void VerletParticle::ComputeFinalPosition(const float &timestep)
{
    Particle::ComputeFinalPosition(timestep);
}

void VerletParticle::ApplyCorrection(const float &timestep)
{
    Particle::ApplyCorrection(timestep);
}
