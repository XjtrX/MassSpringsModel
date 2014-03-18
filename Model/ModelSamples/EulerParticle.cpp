#include "EulerParticle.h"

EulerParticle::EulerParticle(const ParticleState &initialState, const float &massVolume
                             , const float &borderRadius, const int &st)
    :Particle(initialState, massVolume, borderRadius, st)
{
}

EulerParticle::~EulerParticle()
{
}

void EulerParticle::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    Particle::ApplyForce(fX, fY, fZ);
}

void EulerParticle::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    Particle::ApplyAcceleration(aX, aY, aZ);
}

void EulerParticle::CalculateAverageVelocity(const float &timestep)
{
    Particle::CalculateAverageVelocity(timestep);
}


void EulerParticle::Accelerate(const float &timestep)
{
    Particle::Accelerate(timestep);
}

void EulerParticle::Move(const float &timestep)
{
    if (_static)
    {
        _state._position = _prevState._position;
        _state._velocity.set(0, 0, 0);
        _appliedForce.set(0, 0, 0);
        return;
    }

    _prevState = _state;

}

void EulerParticle::setVelocity(const Point3D<float> &newVelocity, const float &timestep)
{
    _state._velocity = newVelocity;
}


void EulerParticle::ComputeFinalPosition(const float &timestep)
{
    Particle::ComputeFinalPosition(timestep);
}
