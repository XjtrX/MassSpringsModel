#ifndef SPRING_H
#define SPRING_H

#include "Mass.h"
#include <math.h>
using namespace std;

class Spring_old
{
public:
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

        Point3D<float> a = _massA->getPosition();
        Point3D<float> b = _massB->getPosition();

        float dX = b.getX() - a.getX();
        float dY = b.getY() - a.getY();

        float dist = sqrt(dX * dX + dY * dY);
        _elasticity = dist;
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
        Point3D<float> a = _massA->_position;
        Point3D<float> b = _massB->_position;

        float dX = b.getX() - a.getX();
        float dY = b.getY() - a.getY();

        float h = sqrt(dX * dX + dY * dY);
/*
        if (_maxLength < dist)
        {
            return 1;
        }
*/
        float diff = _nLength - h;
        float offX = (diff * dX / h) / 2;
        float offY = (diff * dY / h) / 2;

//        _massA->ApplyForce(-offX, -offY, 0);
//        _massB->ApplyForce( offX,  offY, 0);
        _massA->_prevPosition.PlusX(offX);
        _massA->_prevPosition.PlusY(offY);

        _massB->_prevPosition.PlusX(-offX);
        _massB->_prevPosition.PlusY(-offY);

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
