#include "VerletSpringsObject.h"

VerletSpringsObject::VerletSpringsObject(int particlesCount, int springsCount)
    : _particlesCount(particlesCount), _springsCount(springsCount)
    , _particles(particlesCount), _springs(springsCount)
{
}

VerletSpringsObject::~VerletSpringsObject()
{

}

void VerletSpringsObject::Draw()
{  
    glBegin(GL_LINES);

     for (int i = 0; i < this->_springsCount; i++)
     {
         Point3D<float> p = this->_springs[i]->getParticleA()->Position();
         glVertex3f(p.getX(), p.getY(), p.getZ());
         p = this->_springs[i]->getParticleB()->Position();
         glVertex3f(p.getX(), p.getY(), p.getZ());
     }

     glEnd();
}

void VerletSpringsObject::RecalculateSprings()
{
    for (int i = 0; i < _springsCount; i++)
    {
        _springs[i]->Recalculate();
    }
}

void VerletSpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->ApplyForce(fX, fY ,fZ);
    }
}

void VerletSpringsObject::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->ApplyAcceleration(fX, fY ,fZ);
    }
}

void VerletSpringsObject::Accelerate(const float &timeStep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->Accelerate(timeStep);
    }
}

void VerletSpringsObject::Move()
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->Move();
    }
}

void VerletSpringsObject::Collide(int flag)
{
}
