#include "Model/ModelSamples/RungeKuttaParticle.h"

RungeKuttaParticle::RungeKuttaParticle()
{
}

RungeKuttaParticle::RungeKuttaParticle(const ParticleState &initialState
                                       , const float massVolume
                                       , const float borderRadius, const int st)
    : Particle(initialState, massVolume, borderRadius, st)
{

}

RungeKuttaParticle::~RungeKuttaParticle()
{
}
