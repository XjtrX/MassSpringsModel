#include "RungeKuttaSpringsObject.h"
#include "Model/ModelSamples/RungeKuttaParticle.h"

#include <iostream>
using namespace std;

RungeKuttaSpringsObject::RungeKuttaSpringsObject(int particlesCount, int springsCount)
    : SpringsObject(particlesCount, springsCount)
{
}

RungeKuttaSpringsObject::~RungeKuttaSpringsObject()
{
}

void RungeKuttaSpringsObject::ComputeK1(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        dynamic_cast<RungeKuttaParticle*>(_particles[i])->ComputeK1(timestep);
    }
}

void RungeKuttaSpringsObject::ComputeK2(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        dynamic_cast<RungeKuttaParticle*>(_particles[i])->ComputeK2(timestep);
    }
}

void RungeKuttaSpringsObject::ComputeK3(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        dynamic_cast<RungeKuttaParticle*>(_particles[i])->ComputeK3(timestep);
    }
}

void RungeKuttaSpringsObject::ComputeK4(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        dynamic_cast<RungeKuttaParticle*>(_particles[i])->ComputeK4(timestep);
    }
}

void RungeKuttaSpringsObject::Iteration(float timeInterval)
{
    MoveEachOther(timeInterval);
    return;

    ApplyAcceleration(0, -9.8, 0);
    RecalculateSprings();
    ComputeK1(timeInterval);
    ApplyAcceleration(0, -9.8, 0);
    RecalculateSprings();
    ComputeK2(timeInterval);
    ApplyAcceleration(0, -9.8, 0);
    RecalculateSprings();
    ComputeK3(timeInterval);
    ApplyAcceleration(0, -9.8, 0);
    RecalculateSprings();
    ComputeK4(timeInterval);
    Move();
}

void RungeKuttaSpringsObject::Move()
{
    SpringsObject::Move();
}

void RungeKuttaSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyForce(fX, fY, fZ);
}

void RungeKuttaSpringsObject::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyAcceleration(fX, fY, fZ);
}

void RungeKuttaSpringsObject::MoveEachOther(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        RungeKuttaParticle* rKP = dynamic_cast<RungeKuttaParticle*>(_particles.at(i));
        rKP->ApplyAcceleration(0, -9.8, 0);
        rKP->RecalculateConnectionsAffort();
        rKP->ComputeK1(timestep);

        rKP->ApplyAcceleration(0, -9.8, 0);
        rKP->RecalculateConnectionsAffort();
        rKP->ComputeK2(timestep);

        rKP->ApplyAcceleration(0, -9.8, 0);
        rKP->RecalculateConnectionsAffort();
        rKP->ComputeK3(timestep);

        rKP->ApplyAcceleration(0, -9.8, 0);
        rKP->RecalculateConnectionsAffort();
        rKP->ComputeK4(timestep);

        rKP->Move();
    }
    //Move();
}
