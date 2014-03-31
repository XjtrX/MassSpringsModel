#include "VerletSpringsObject.h"
#include "Model/ModelSamples/VerletParticle.h"
#include "3DMath/MathRotation.h"

VerletSpringsObject::VerletSpringsObject(const int &cols, const int &rows, const float &width, const float &height
                                         , const float &massVolume, const float &stiffnes, const float &thickness
                                         , const Point3D<float> &rotation, const Point3D<float> &translation
                                         , const int &withBendSprings)
    :SpringsObject(cols * rows
                   ,   (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1)
                     + ((cols - 2) * rows + cols * (rows - 2)) * (withBendSprings == 1 ? 1 : 0)
                   , (cols - 1) * rows + cols * (rows - 1)
                   , (cols - 1) * (rows - 1) * 2, thickness)
 {
     float massOfParticle = massVolume / _particlesCount;

     MathRotation m;
     float* rotMatr = m.RotationMatrix(rotation._x
                                                  , rotation._y
                                                  , rotation._z);
     for (int r = 0; r < rows; r++)
     {
         for (int c = 0; c < cols; c++)
         {
             _particles[r * cols + c] = new VerletParticle(
                         ParticleState(
                             m.RotateAndTranslatePoint(
                                 Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows)
                                 , rotMatr, translation), Point3D<float>(0, 0, 0))
                         , massOfParticle);
         }
     }
     delete[] rotMatr;

     this->ConnectParticles(cols, rows, width, height, stiffnes, withBendSprings);
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

void VerletSpringsObject::Inertia(const float &timestep)
{
    SpringsObject::Inertia(timestep);
}

void VerletSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyForce(fX, fY, fZ);
}

void VerletSpringsObject::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    SpringsObject::ApplyAcceleration(aX, aY, aZ);
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

void VerletSpringsObject::ApplyCorrection(const float &timestep)
{
    SpringsObject::ApplyCorrection(timestep);
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
    this->Accelerate(timeInterval);
    this->Inertia(timeInterval);
}
