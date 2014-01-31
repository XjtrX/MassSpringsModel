#include "ParticlePosition.h"

ParticlePosition::ParticlePosition()
{
}

ParticlePosition::ParticlePosition(const Point3D<float> &p)
{
    this->_position = p;
}

ParticlePosition::ParticlePosition(const ParticlePosition &other)
{
    this->_position = other._position;
}

ParticlePosition::~ParticlePosition()
{
}

ParticlePosition &ParticlePosition::operator +=(const ParticlePosition &other)
{
    this->_position += other._position;
    return *this;
}

ParticlePosition &ParticlePosition::operator -=(const ParticlePosition &other)

{
    this->_position -= other._position;
    return *this;
}

ParticlePosition &ParticlePosition::operator *=(const float &coeff)
{
    this->_position *= coeff;
    return *this;
}
