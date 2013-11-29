#ifndef SPRING_H
#define SPRING_H

#include "Mass.h"
#include <math.h>

//#include <iostream>
using namespace std;

class Spring
{
private:
//    Mass& _massA;
//    Mass& _massB;
    Mass* _massA;
    Mass* _massB;
    float _nLength;
    float _maxLength;
    float _elasticity;

public:
    Spring()
    {

    }

    Spring(Mass* massA, Mass* massB, float nLength, float maxLength, float elasticity)
    {
        _massA = massA;
        _massB = massB;
        _nLength = nLength;
        _maxLength = maxLength;
        _elasticity = elasticity;
    }

    Spring(const Spring& other)
    {
        this->_massA = other._massA;
        this->_massB = other._massB;
        this->_nLength = other._nLength;
        this->_maxLength = other._maxLength;
        this->_elasticity = other._elasticity;
    }

    ~Spring()
    {
        //
    }

    Spring& operator=(const Spring& other)
    {
        if (this != &other)
        {
            this->_massA = other._massA;
            this->_massB = other._massB;
            this->_nLength = other._nLength;
            this->_maxLength = other._maxLength;
            this->_elasticity = other._elasticity;
        }

        return *this;
    }

    int Recalculate()
    {
        Point3D<float> a = _massA->getPosition();
        Point3D<float> b = _massB->getPosition();

        float dX = b.getX() - a.getX();
        float dY = b.getY() - a.getY();
        float dZ = b.getZ() - a.getZ();

        float dist = sqrt(dX * dX + dY * dY + dZ * dZ);

        if (_maxLength < dist)
        {
            return 1;
        }

        float offX = ((_nLength - dist) * dX / dist) * _elasticity;
        float offY = ((_nLength - dist) * dY / dist) * _elasticity;
        float offZ = ((_nLength - dist) * dZ / dist) * _elasticity;

        //cout << "offX" << offX << " offY " << offY << " offZ " << offZ << endl;
        //cout.flush();
        _massA->ApplyForce(-offX, -offY, -offZ);
        _massB->ApplyForce( offX,  offY,  offZ);
        return 0;
    }

    Mass* getMassA()
    {
        return _massA;
    }

    Mass* getMassB()
    {
        return _massB;
    }
};

#endif // SPRING_H
