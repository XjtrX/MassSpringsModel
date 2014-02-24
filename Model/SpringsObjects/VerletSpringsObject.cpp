#include "VerletSpringsObject.h"

VerletSpringsObject::VerletSpringsObject(int particlesCount, int springsCount, int structuralSpringsCount, int clothTrianglesCount)
    : SpringsObject(particlesCount, springsCount, structuralSpringsCount, clothTrianglesCount)
{
}

VerletSpringsObject::~VerletSpringsObject()
{

}

void VerletSpringsObject::Collide(int flag)
{
    SpringsObject::Collide(flag);
}

void VerletSpringsObject::Accelerate(const float &timeStep)
{
    SpringsObject::Accelerate(timeStep);
}

void VerletSpringsObject::Move()
{
    SpringsObject::Move();
}

void VerletSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyForce(fX, fY, fZ);
}

void VerletSpringsObject::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyAcceleration(fX, fY, fZ);
}

void VerletSpringsObject::Iteration(float timeInterval)
{
    /*
    _scene.ApplyAcceleration(0, -9.8, 0);
    _scene.RecalculateSprings();
    _scene.Accelerate(_timeInterval);
    //_scene.Collide(false);
    _scene.Move();
    //_scene.Collide(true);
    //_scene.RecalculateSprings();
    //_scene.Accelerate(1.0 / 24);
    */

    this->ApplyAcceleration(0, -9.8, 0);
    this->RecalculateSprings();
    this->Accelerate(timeInterval);
    this->Move();
}
