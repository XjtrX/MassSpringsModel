#include "Model/ModelSamples/Particle.h"

Particle::Particle(const Particle &particle)
{
    this->_state = particle._state;
    this->_prevState = particle._prevState;
    this->_averageVelocity = particle._averageVelocity;
    this->_approximateVelocity = particle._approximateVelocity;
    this->_appliedForce = particle._appliedForce;
    this->_dV = particle._dV;
    this->_massVolume = particle._massVolume;
    this->_borderRadius = particle._borderRadius;
    this->_static = particle._static;
}

Particle::Particle(const ParticleState& initialState
                   , const float& massVolume, const float& borderRadius, const int& st)
{
    _state = initialState;
    _prevState = initialState;
//    _averageVelocity.set(0, 0, 0);
//    _appliedForce.set(0, 0, 0);
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
        glTranslatef(_state._position.getX()
                     , _state._position.getY()
                     , _state._position.getZ());
        gluSphere(Sphere, _borderRadius, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(Sphere);
}

Point3D<float>& Particle::getPosition()
{
    return _state._position;
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

void Particle::CalculateAverageVelocity(const float &timestep)
{
    _averageVelocity = (_state._position - _prevState._position) / timestep;
    _approximateVelocity = _averageVelocity;
    _collided = 0;
}

void Particle::Accelerate(const float &timestep)
{
    if (_static)
    {
        return;
    }

    Point3D<float> acceleration = _appliedForce / _massVolume;
    _state._velocity += acceleration * timestep;
    _state._position += acceleration * timestep *  timestep / 2;

     _appliedForce.set(0, 0, 0);
}

Point3D<float> Particle::getVelocity()
{
    return _state._velocity;
}

void Particle::ComputeFinalPosition(const float &timestep)
{
    if (1 || _collided)
    {
        _state._position = _prevState._position + _approximateVelocity * timestep;
        this->setVelocity((_approximateVelocity + _prevState._velocity) / 2, timestep);
//        this->setVelocity((this->_state._position - this->_prevState._position) / timestep, timestep);
//        this->setVelocity(_approximateVelocity, timestep);
    }
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
