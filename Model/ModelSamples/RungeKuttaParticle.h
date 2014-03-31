#ifndef RUNGEKUTTAPARTICLE_H
#define RUNGEKUTTAPARTICLE_H

#include "Model/ModelSamples/Particle.h"
#include "3DMath/ParticleState.h"
#include "Model/Interfaces/RungeKuttaObject.h"

#include "Model/ModelSamples/Spring.h"

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
    virtual ~ConnectedParticle()
    {
//        cout << "deleted\n";
//        cout.flush();
    }
};

#include "Model/ModelSamples/ClothTriangle.h"

struct TriangleToCollide
{
    ClothTriangle* _tO;
    float _aDP;

    TriangleToCollide(ClothTriangle* tO)
    {
        _tO = tO;
    }

    virtual ~TriangleToCollide()
    {
    }
};

class RungeKuttaParticle: public Particle, public RungeKuttaObject
{
public:
    RungeKuttaParticle(const ParticleState& initialState
                       , const float &massVolume, const float &borderRadius = 1
                       , const int &st = 0);
    virtual ~RungeKuttaParticle();

    virtual void Inertia(const float &timestep);

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void Accelerate(const float &timestep);
    virtual void CalculateAverageVelocity(const float &timestep);

    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual Point3D<float> getVelocity();
    virtual void ComputeFinalPosition(const float &timestep);
    virtual void ApplyCorrection(const float &timestep);

    virtual ParticleState RKTransformation(const ParticleState particleState, float dt);
    virtual void ComputeK1(float timestep);
    virtual void ComputeK2(float timestep);
    virtual void ComputeK3(float timestep);
    virtual void ComputeK4(float timestep);

    void AddConnection(Spring* spring, Particle* particle);
    void RecalculateConnectionsAffort();

public:
    ParticleState _interm;
    ParticleState _k1;
    ParticleState _k2;
    ParticleState _k3;
    ParticleState _k4;

    vector<ConnectedParticle*> _connections;
    vector<TriangleToCollide*> _triangles;
};

#endif // RUNGEKUTTAPARTICLE_H
