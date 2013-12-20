#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(Point3D<float> initialPosition, float massVolume, float borderRadius
                   , int st)
{
    _prevPosition = initialPosition;
    _position = initialPosition;
    _appliedForce.set(0, 0, 0);
    _massVolume = massVolume;
    _static = st;
    _borderRadius = borderRadius;
}

Particle::~Particle()
{
}

void Particle::Move()
{
    if (_static)
    {
        _position = _prevPosition;
        _appliedForce.set(0, 0, 0);
        return;
    }

    Point3D<float> temp = _position;
    //_position.Plus(_position);
    _position += _position;
    //_position.Minus(_prevPosition);
    _position -= _prevPosition;
    //_position.Plus(_appliedForce);
    _prevPosition = temp;
    //_appliedForce.set(0, 0, 0);
}

void Particle::Accelerate(const float &timeStep)
{
    float koeff = timeStep * timeStep / 2 / _massVolume;
    _position.PlusX(_appliedForce.getX() * koeff);
    _position.PlusY(_appliedForce.getY() * koeff);
    _position.PlusZ(_appliedForce.getZ() * koeff);
    _appliedForce.set(0, 0, 0);
}

Point3D<float>& Particle::PrevPosition()
{
    return _prevPosition;
}

Point3D<float>& Particle::Position()
{
    return _position;
}

void Particle::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    _appliedForce.PlusX(fX);
    _appliedForce.PlusY(fY);
    _appliedForce.PlusZ(fZ);
}

void Particle::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    _appliedForce.PlusX(fX * _massVolume);
    _appliedForce.PlusY(fY * _massVolume);
    _appliedForce.PlusZ(fZ * _massVolume);
}

void Particle::Collide(int flag)
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
