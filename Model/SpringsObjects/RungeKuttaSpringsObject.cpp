#include "RungeKuttaSpringsObject.h"

#include "3DMath/MathRotation.h"

#include <iostream>
#include "omp.h"
using namespace std;

void AddConnections(Particle* p1, Particle* p2, Spring* s)
{
    dynamic_cast<RungeKuttaParticle*>(p1)->AddConnection(s, p2);
    dynamic_cast<RungeKuttaParticle*>(p2)->AddConnection(s, p1);
}

RungeKuttaSpringsObject::RungeKuttaSpringsObject(const int &cols, const int &rows
                                                 , const float &width, const float &height
                                                 , const float &massVolume, const float &stiffnes
                                                 , const float &thickness
                                                 , const Point3D<float> &rotation
                                                 , const Point3D<float> &translation
                                                 , const int &withBendSprings)
    :SpringsObject(cols * rows
                   ,   (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1)
                     + ((cols - 2) * rows + cols * (rows - 2)) * (withBendSprings == 1 ? 1 : 0)
                   , (cols - 1) * rows + cols * (rows - 1)
                   , (cols - 1) * (rows - 1) * 2, thickness)
{
    _rKParticles = vector<RungeKuttaParticle*>(this->_particlesCount);

    float massOfParticle = massVolume / _particlesCount;

    MathRotation m;
    float* rotMatr = m.RotationMatrix(rotation._x
                                                 , rotation._y
                                                 , rotation._z);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            _rKParticles[r * cols + c] = new RungeKuttaParticle(
                        ParticleState(
                            m.RotateAndTranslatePoint(
                                Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows)
                                , rotMatr, translation), Point3D<float>(0, 0, 0))
                        , massOfParticle);
            _particles[r * cols + c] = _rKParticles[r * cols + c];
//            _particles[r * cols + c] = new RungeKuttaParticle(
//                        ParticleState(
//                            m.RotateAndTranslatePoint(
//                                Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows)
//                                , rotMatr, translation), Point3D<float>(0, 0, 0))
//                        , massOfParticle);
        }
    }
    delete[] rotMatr;

    this->ConnectParticles(cols, rows, width, height, stiffnes, withBendSprings);

    for (int i = 0; i < _springsCount; i++)
    {
        Spring* s = _springs[i];
        AddConnections(s->_particleA, s->_particleB, s);
    }
}

RungeKuttaSpringsObject::~RungeKuttaSpringsObject()
{

}

void RungeKuttaSpringsObject::ComputeK1(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _rKParticles[i]->ComputeK1(timestep);
    }
}

void RungeKuttaSpringsObject::ComputeK2(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _rKParticles[i]->ComputeK2(timestep);
    }
}

void RungeKuttaSpringsObject::ComputeK3(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _rKParticles[i]->ComputeK3(timestep);
    }
}

void RungeKuttaSpringsObject::ComputeK4(float timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _rKParticles[i]->ComputeK4(timestep);
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

void RungeKuttaSpringsObject::Inertia(const float &timestep)
{
    SpringsObject::Inertia(timestep);
}

inline void RungeKuttaSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyForce(fX, fY, fZ);
}

inline void RungeKuttaSpringsObject::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    SpringsObject::ApplyAcceleration(aX, aY, aZ);
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

void RungeKuttaSpringsObject::ComputeFinalPosition(const float &timestep)
{
    SpringsObject::ComputeFinalPosition(timestep);
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
        RungeKuttaParticle* rKP = _rKParticles.at(i);
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
    Inertia(timestep);
}

void RungeKuttaSpringsObject::RecalculateConnectionsAffort()
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _rKParticles[i]->RecalculateConnectionsAffort();
    }
}
