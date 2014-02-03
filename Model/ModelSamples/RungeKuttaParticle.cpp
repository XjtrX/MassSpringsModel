#include "Model/ModelSamples/RungeKuttaParticle.h"

#include <iostream>
using namespace std;

RungeKuttaParticle::RungeKuttaParticle()
{
}

RungeKuttaParticle::RungeKuttaParticle(const ParticleState &initialState
                                       , const float massVolume
                                       , const float borderRadius, const int st)
    : Particle(initialState, massVolume, borderRadius, st)
{
    _prev = initialState;
}

RungeKuttaParticle::~RungeKuttaParticle()
{
}

void RungeKuttaParticle::Collide(int)
{
}

void RungeKuttaParticle::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    _appliedForce.PlusX(fX);
    _appliedForce.PlusY(fY);
    _appliedForce.PlusZ(fZ);
}

void RungeKuttaParticle::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    _appliedForce.PlusX(aX * _massVolume);
    _appliedForce.PlusY(aY * _massVolume);
    _appliedForce.PlusZ(aZ * _massVolume);
}

void RungeKuttaParticle::Move()
{
    if (_static)
    {
        return;
    }
    _prev += _k1 / 6;
    _prev += _k2 / 3;
    _prev += _k3 / 3;
    _prev += _k4 / 6;
    _position = _prev;

}

ParticleState RungeKuttaParticle::RKTransformation(const ParticleState particleState, float)
{
    ParticleState res;
    res._position = particleState._velocity;
    res._velocity = this->_appliedForce / _massVolume;
    _appliedForce.set(0, 0, 0);
    return res;
}

void RungeKuttaParticle::ComputeK1(float timestep)
{
    if (_static)
    {
        return;
    }
    _k1 = RKTransformation(_prev, timestep) * timestep;
    _position = _prev + _k1 * 0.5;
}

void RungeKuttaParticle::ComputeK2(float timestep)
{
    if (_static)
    {
        return;
    }
    _k2 = RKTransformation(_prev + _k1 * 0.5, timestep) * timestep;
    _position = _prev + _k2 * 0.5;
}

void RungeKuttaParticle::ComputeK3(float timestep)
{
    if (_static)
    {
        return;
    }
    _k3 = RKTransformation(_prev + _k2 * 0.5, timestep) * timestep;
    _position = _prev + _k3;
}

void RungeKuttaParticle::ComputeK4(float timestep)
{
    if (_static)
    {
        return;
    }
    _k4 = RKTransformation(_prev + _k3, timestep) * timestep;
}
