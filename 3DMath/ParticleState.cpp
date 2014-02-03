#include "ParticleState.h"

ParticleState::ParticleState()
{
}

ParticleState::~ParticleState()
{
}

ParticleState::ParticleState(const ParticleState &ps): ParticlePosition()
{
    this->_position = ps._position;
    this->_velocity = ps._velocity;
}

ParticleState::ParticleState(const Point3D<float> &position, const Point3D<float> &velocity)
    : ParticlePosition(position), _velocity(velocity)
{
}

ParticleState &ParticleState::operator +=(const ParticleState &other)
{
    this->_position += other._position;
    this->_velocity += other._velocity;
    return *this;
}

ParticleState &ParticleState::operator *=(const float &coeff)
{
    this->_position *= coeff;
    this->_velocity *= coeff;
    return *this;
}

ParticleState ParticleState::operator /(const float &coeff)
{
    ParticleState res(*this);
    res._position /= coeff;
    res._velocity /= coeff;
    return res;
}

ParticleState ParticleState::operator +(const ParticleState& other)
{
    ParticleState res(*this);
    res._position += other._position;
    res._velocity += other._velocity;
    return res;
}

ParticleState ParticleState::operator *(const float& coeff)
{
    ParticleState res(*this);
    res._position *= coeff;
    res._velocity *= coeff;
    return res;
}
