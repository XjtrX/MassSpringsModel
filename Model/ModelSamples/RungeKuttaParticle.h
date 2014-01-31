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

    virtual void Collide(int flag) = 0;
};

#endif // RUNGEKUTTAPARTICLE_H
