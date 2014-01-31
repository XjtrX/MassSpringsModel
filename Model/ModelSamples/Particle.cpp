#include "Model/ModelSamples/Particle.h"

Particle::Particle()
{
}

Particle::Particle(const Particle &particle)
{
    this->_position = particle._position;
    this->_massVolume = particle._massVolume;
    this->_borderRadius = particle._borderRadius;
    this->_static = particle._static;
}

Particle::Particle(const Point3D<float>& initialPosition
                   , const float& massVolume, const float& borderRadius, const int& st)
{
    _position = initialPosition;
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
        glTranslatef(_position.getX(), _position.getY(), _position.getZ());
        gluSphere(Sphere, _borderRadius, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(Sphere);
}

Point3D<float>& Particle::Position()
{
    return _position;
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
