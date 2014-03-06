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
    _interm = initialState;
}

RungeKuttaParticle::~RungeKuttaParticle()
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

void RungeKuttaParticle::Accelerate(const float &timestep)
{
    Particle::Accelerate(timestep);
}

void RungeKuttaParticle::CalculateAverageVelocity(const float &timestep)
{
    Particle::CalculateAverageVelocity(timestep);
}

void RungeKuttaParticle::setVelocity(const Point3D<float> &newVelocity, const float &)
{
    _state._velocity = newVelocity;
}

Point3D<float> RungeKuttaParticle::getVelocity()
{
    return _state._velocity;
}

void RungeKuttaParticle::Move(const float &)
{
    if (_static)
    {
        return;
    }
    _prevState = _interm;
    _interm += _k1 / 6;
    _interm += _k2 / 3;
    _interm += _k3 / 3;
    _interm += _k4 / 6;
    _state = _interm;
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
    _interm = _state;
    if (_static)
    {
        return;
    }
    _k1 = RKTransformation(_interm, timestep) * timestep;
    _state = _interm + _k1 * 0.5;
}

void RungeKuttaParticle::ComputeK2(float timestep)
{
    if (_static)
    {
        return;
    }
    _k2 = RKTransformation(_interm + _k1 * 0.5, timestep) * timestep;
    _state = _interm + _k2 * 0.5;
}

void RungeKuttaParticle::ComputeK3(float timestep)
{
    if (_static)
    {
        return;
    }
    _k3 = RKTransformation(_interm + _k2 * 0.5, timestep) * timestep;
    _state = _interm + _k3;
}

void RungeKuttaParticle::ComputeK4(float timestep)
{
    if (_static)
    {
        return;
    }
    _k4 = RKTransformation(_interm + _k3, timestep) * timestep;
}

void RungeKuttaParticle::Collide(const float &)
{
}

void RungeKuttaParticle::AddConnection(Spring* spring, Particle* particle)
{
    ConnectedParticle* cP = new ConnectedParticle(spring, particle);
    _connections.push_back(cP);
}

void RungeKuttaParticle::RecalculateConnectionsAffort()
{
    int l = _connections.size();
    for (int i = 0; i < l; i++)
    {
        Spring* s = _connections.at(i)->_spring;
        RungeKuttaParticle* p = dynamic_cast<RungeKuttaParticle*>(_connections.at(i)->_particle);

        Point3D<float> pA = this->getPosition();
        Point3D<float> pB = p->getPosition();
        Point3D<float> dist = pA;
        dist -= pB;

        float distLen = sqrt(dist.getSquaredLength());

        float diff = s->_nLentght - distLen;

        float kDamp = 0.01;

        Point3D<float> diffVel = this->_state._velocity;
        diffVel -= p->_state._velocity;

        float stiffness = s->_stiffness;
        float fX = diff * dist.getX() / distLen * stiffness - diffVel.getX() * kDamp;
        float fY = diff * dist.getY() / distLen * stiffness - diffVel.getY() * kDamp;
        float fZ = diff * dist.getZ() / distLen * stiffness - diffVel.getZ() * kDamp;

        this->ApplyForce(fX, fY, fZ);
    }
}
