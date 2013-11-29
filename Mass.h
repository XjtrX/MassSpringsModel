#ifndef MASS_H
#define MASS_H

#include "Point3D.h"

class Mass
{
private:
    Point3D<float> _prevPosition;
    Point3D<float> _position;
    float _massVolume;
    Point3D<float> _appliedForce;
    int _static;

public: 
    Mass()
    {

    }

    Mass(Point3D<float> position, float massVolume, int st):_appliedForce(0.0, 0.0, 0.0)
    {
        _prevPosition = position;
        _position = position;
        _massVolume = massVolume;
        _static = st;
    }

    Mass(const Mass& other)
    {
        this->_prevPosition = other._prevPosition;
        this->_position = other._position;
        this->_massVolume = other._massVolume;
        this->_appliedForce = other._appliedForce;
        this->_static = other._static;
    }

    Mass& operator=(const Mass& other)
    {
        if (this != &other)
        {
            this->_prevPosition = other._prevPosition;
            this->_position = other._position;
            this->_massVolume = other._massVolume;
            this->_appliedForce = other._appliedForce;
            this->_static = other._static;
        }

        return *this;
    }

    void Move(float deltaTime)
    {
        if (_static)
        {
            return;
        }
        Point3D<float> temp = _position;
        _position += _position;
        _position -= _prevPosition;
        _position += _appliedForce * deltaTime * deltaTime / _massVolume / 2;
        _prevPosition = temp;
        _appliedForce.set(0, 0, 0);
    }

    int isStatic()
    {
        return _static;
    }

    void setStatic(int st)
    {
        _static = st;
    }

    Point3D<float> getPrevPosition()
    {
        return _prevPosition;
    }

    Point3D<float> getPosition()
    {
        return _position;
    }

    float getMassVolume()
    {
        return _massVolume;
    }

    void ApplyForce(float fX, float fY, float fZ)
    {
        _appliedForce.PlusX(fX);
        _appliedForce.PlusY(fY);
        _appliedForce.PlusZ(fZ);
    }
};

#endif // MASS_H
