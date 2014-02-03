#ifndef RUNGEKUTTAPARTICLE_H
#define RUNGEKUTTAPARTICLE_H

#include "Unresolved/Particle.h"
#include "3DMath/ParticleState.h"
#include "Model/Interfaces/RungeKuttaObject.h"

class RungeKuttaParticle: public Particle, public RungeKuttaObject
{
public:
    RungeKuttaParticle();
    RungeKuttaParticle(const ParticleState& initialState
                       , const float massVolume, const float borderRadius = 1
                       , const int st = 0);
    virtual ~RungeKuttaParticle();

    virtual void Collide(int flag);
    virtual void Move();

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);

    virtual ParticleState RKTransformation(const ParticleState particleState, float dt);
    virtual void ComputeK1(float timestep);
    virtual void ComputeK2(float timestep);
    virtual void ComputeK3(float timestep);
    virtual void ComputeK4(float timestep);

public:
    ParticleState _prev;
    ParticleState _k1;
    ParticleState _k2;
    ParticleState _k3;
    ParticleState _k4;
};

#endif // RUNGEKUTTAPARTICLE_H
