#include "Model/ModelSamples/Unresolved/Particle.h"

Particle::Particle()
{
}

Particle::Particle(const Particle &particle)
{
    this->_position = particle._position;
    this->_prevPosition = particle._prevPosition;
    this->_massVolume = particle._massVolume;
    this->_borderRadius = particle._borderRadius;
    this->_static = particle._static;
}

Particle::Particle(const ParticlePosition& initialPosition
                   , const float& massVolume, const float& borderRadius, const int& st)
{
    _position = initialPosition;
    _prevPosition = initialPosition;
    _massVolume = massVolume;
    _borderRadius = borderRadius;
    _static = st;
}

Particle::~Particle()
{
}

void Particle::Draw()
{
    GLUquadricObj* Sphere;
    Sphere = gluNewQuadric();
    glPushMatrix();
        glTranslatef(_position._position.getX()
                     , _position._position.getY()
                     , _position._position.getZ());
        gluSphere(Sphere, _borderRadius, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(Sphere);
}

Point3D<float>& Particle::getPosition()
{
    return _position._position;
}

void Particle::Accelerate(const float &timeStep)
{
        float koeff = timeStep * timeStep / 2 / _massVolume;
        _position._position.PlusX(_appliedForce.getX() * koeff);
        _position._position.PlusY(_appliedForce.getY() * koeff);
        _position._position.PlusZ(_appliedForce.getZ() * koeff);
        _appliedForce.set(0, 0, 0);
}

void Particle::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    _appliedForce.PlusX(fX);
    _appliedForce.PlusY(fY);
    _appliedForce.PlusZ(fZ);
}

void Particle::ApplyAcceleration(const float &aX, const float &aY, const float &aZ)
{
    _appliedForce.PlusX(aX * _massVolume);
    _appliedForce.PlusY(aY * _massVolume);
    _appliedForce.PlusZ(aZ * _massVolume);
}

void Particle::Collide(int)
{
}


int Particle::isStatic()
{
    return _static;
}

void Particle::setStatic(int st)
{
    _static = st;
}

float Particle::getBorderRadius()
{
    return _borderRadius;
}

float Particle::getMassVolume()
{
    return _massVolume;
}
