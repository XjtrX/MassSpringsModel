#include "EulerSpringsObject.h"
#include "3DMath/MathRotation.h"

EulerSpringsObject::EulerSpringsObject(const int &cols, const int &rows, const float &width, const float &height
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
            _particles[r * cols + c] = new EulerParticle(
                        ParticleState(
                            m.RotateAndTranslatePoint(
                                Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows)
                                , rotMatr, translation), Point3D<float>(0, 0, 0))
                        , massOfParticle);
        }
    }
    delete[] rotMatr;

    this->ConnectParticles(cols, rows, width, height, massVolume, stiffnes, thickness, rotation, translation
                           , withBendSprings);
}

EulerSpringsObject::~EulerSpringsObject()
{
}

void EulerSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    SpringsObject::ApplyForce(fX, fY, fZ);
}

void EulerSpringsObject::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    SpringsObject::ApplyAcceleration(aX, aY, aZ);
}

void EulerSpringsObject::CalculateAverageVelocity(const float &timestep)
{
    SpringsObject::CalculateAverageVelocity(timestep);
}

void EulerSpringsObject::Accelerate(const float &timestep)
{
    SpringsObject::Accelerate(timestep);
}

void EulerSpringsObject::Move(const float &timestep)
{
    SpringsObject::Move(timestep);
}

void EulerSpringsObject::setVelocity(const Point3D<float> &newVelocity, const float &timestep)
{
    SpringsObject::setVelocity(newVelocity, timestep);
}

void EulerSpringsObject::ComputeFinalPosition(const float &timestep)
{
    SpringsObject::ComputeFinalPosition(timestep);
}

void EulerSpringsObject::Iteration(float timeInterval)
{
    this->ApplyAcceleration(0, -9.8, 0);
    this->RecalculateSprings();
//    this->Accelerate(timeInterval);
//    this->Move();
    this->Move(timeInterval);
    this->Accelerate(timeInterval);
}
