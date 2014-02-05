#ifndef RUNGEKUTTAPARTICLE_H
#define RUNGEKUTTAPARTICLE_H

#include "Unresolved/Particle.h"
#include "3DMath/ParticleState.h"
#include "Model/Interfaces/RungeKuttaObject.h"

#include "Model/ModelSamples/Spring.h"

//#include <iostream>
#include <vector>
using namespace std;

struct ConnectedParticle
{
    Spring* _spring;
    Particle* _particle;

    ConnectedParticle(Spring* spring, Particle* particle)
        :_spring(spring), _particle(particle)
    {
//        cout << "created\n";
//        cout.flush();
    }
    ~ConnectedParticle()
    {
//        cout << "deleted\n";
//        cout.flush();
    }
};

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

    void AddConnection(Spring* spring, Particle* particle);
    void RecalculateConnectionsAffort();

public:
    ParticleState _prev;
    ParticleState _k1;
    ParticleState _k2;
    ParticleState _k3;
    ParticleState _k4;

    vector<ConnectedParticle> _connections;
};

#endif // RUNGEKUTTAPARTICLE_H
