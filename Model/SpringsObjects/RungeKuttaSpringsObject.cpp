#include "RungeKuttaSpringsObject.h"
#include "Model/ModelSamples/RungeKuttaParticle.h"

#include <iostream>
#include "omp.h"
using namespace std;

RungeKuttaSpringsObject::RungeKuttaSpringsObject(const int &particlesCount, const int &springsCount, const int &structuralSpringsCount, const int &clothTrianglesCount, const float &thickness)
    : SpringsObject(particlesCount, springsCount, structuralSpringsCount, clothTrianglesCount, thickness)
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
/*
    ApplyAcceleration(0, -9.8, 0);
    RecalculateConnectionsAffort();
    //RecalculateSprings();
    ComputeK1(timeInterval);
    ApplyAcceleration(0, -9.8, 0);
    RecalculateConnectionsAffort();
    //RecalculateSprings();
    ComputeK2(timeInterval);
    ApplyAcceleration(0, -9.8, 0);
    RecalculateConnectionsAffort();
    //RecalculateSprings();
    ComputeK3(timeInterval);
    ApplyAcceleration(0, -9.8, 0);
    RecalculateConnectionsAffort();
    //RecalculateSprings();
    ComputeK4(timeInterval);
    Move();
*/
}

void RungeKuttaSpringsObject::Move(const float &timestep)
{
    SpringsObject::Move(timestep);
}

inline void RungeKuttaSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyForce(fX, fY, fZ);
}

inline void RungeKuttaSpringsObject::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyAcceleration(fX, fY, fZ);
}

void RungeKuttaSpringsObject::Accelerate(const float &timestep)
{
    SpringsObject::CalculateAverageVelocity(timestep);
}

void RungeKuttaSpringsObject::CalculateAverageVelocity(const float &timestep)
{
    SpringsObject::CalculateAverageVelocity(timestep);
}

void RungeKuttaSpringsObject::setVelocity(const Point3D<float> &newVelocity, const float &timestep)
{
    SpringsObject::setVelocity(newVelocity, timestep);
}

Point3D<float> RungeKuttaSpringsObject::getVelocity()
{
    return SpringsObject::getVelocity();
}

inline void RungeKuttaSpringsObject::Collide(const float &timestep)
{
    SpringsObject::Collide(timestep);
}

void RungeKuttaSpringsObject::ResolveCollisions(const float &timestep)
{
    SpringsObject::ResolveCollisions(timestep);
}

void RungeKuttaSpringsObject::MoveEachOther(const float &timestep)
{

    #pragma omp parallel for
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
    }
    Move(timestep);
}

void RungeKuttaSpringsObject::RecalculateConnectionsAffort()
{
    for (int i = 0; i < _particlesCount; i++)
    {
        dynamic_cast<RungeKuttaParticle*>(_particles[i])->RecalculateConnectionsAffort();
    }
}
