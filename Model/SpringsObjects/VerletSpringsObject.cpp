#include "VerletSpringsObject.h"

VerletSpringsObject::VerletSpringsObject(const int &particlesCount, const int &springsCount, const int &structuralSpringsCount, const int &clothTrianglesCount, const float &thickness)
    : SpringsObject(particlesCount, springsCount, structuralSpringsCount, clothTrianglesCount, thickness)
{
}

VerletSpringsObject::~VerletSpringsObject()
{

}

void VerletSpringsObject::Collide(const float &timestep)
{
    SpringsObject::Collide(timestep);
}

void VerletSpringsObject::Accelerate(const float &timestep)
{
    SpringsObject::Accelerate(timestep);
}

void VerletSpringsObject::Move(const float &timestep)
{
    SpringsObject::Move(timestep);
}

void VerletSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyForce(fX, fY, fZ);
}

void VerletSpringsObject::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyAcceleration(fX, fY, fZ);
}

void VerletSpringsObject::setVelocity(const Point3D<float> &newVelocity, const float &timestep)
{
    SpringsObject::setVelocity(newVelocity, timestep);
}

Point3D<float> VerletSpringsObject::getVelocity()
{
    return SpringsObject::getVelocity();
}

void VerletSpringsObject::CalculateAverageVelocity(const float &timestep)
{
    SpringsObject::CalculateAverageVelocity(timestep);
}

void VerletSpringsObject::ComputeFinalPosition(const float &timestep)
{
    SpringsObject::ComputeFinalPosition(timestep);
}

void VerletSpringsObject::ResolveCollisions(const float &timestep)
{
    SpringsObject::ResolveCollisions(timestep);
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
//    this->Accelerate(timeInterval);
//    this->Move();
    this->Move(timeInterval);
    this->Accelerate(timeInterval);
}
