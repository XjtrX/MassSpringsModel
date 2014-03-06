#ifndef CLOTHTRIANGLE_H
#define CLOTHTRIANGLE_H


#include "Model/Interfaces/DrawableObject.h"
#include "Model/ModelSamples/Unresolved/Particle.h"

#include <math.h>
using namespace std;

class ClothTriangle: public DrawableObject
{
public:
    Particle* _p[3];
    Particle* _connected;

    Point3D<float> _normal;
    float _DCoeff;

    Point3D<float> _prevNormal;
    float _prevDCoeff;

    int _highlighted;

    int _zoneNum;

    ClothTriangle(Particle* p1, Particle* p2, Particle *p3)
    {
        _p[0] = p1;
        _p[1] = p2;
        _p[2] = p3;
        _highlighted = 0;
        _zoneNum = -1;
    }

    virtual ~ClothTriangle()
    {

    }

    void RecalculatePlane()
    {
        _prevNormal = _normal;
        _prevDCoeff = _DCoeff;
        Point3D<float>& A = this->_p[0]->_state._position;
        Point3D<float>& B = this->_p[1]->_state._position;
        Point3D<float>& C = this->_p[2]->_state._position;

        Point3D<float> AB = B;
        AB -= A;

        Point3D<float> AC = C;
        AC -= A;

        this->_normal = Point3D<float>::CrossProduct(AB, AC);
        this->_normal /= sqrt(this->_normal.getSquaredLength());

        _DCoeff = -1 * this->_normal.DotProduct(A);
    }

    Point3D<float> CalculateProjection(const Point3D<float>& p)
    {
        float dP = _normal.DotProduct(p);
        float sL = _normal.getSquaredLength();
        float lambda = -1 * (_DCoeff + dP) / sL;
        Point3D<float> res(  p._x + lambda * _normal._x
                           , p._y + lambda * _normal._y
                           , p._z + lambda * _normal._z);
        return res;
    }

    int isInTriangle(const Point3D<float>& p)
    {
        Point3D<float> AB = _p[1]->_state._position;
        AB -= _p[0]->_state._position;
        Point3D<float> BC = _p[2]->_state._position;
        BC -= _p[1]->_state._position;
        Point3D<float> CA = _p[0]->_state._position;
        CA -= _p[2]->_state._position;

        Point3D<float> AP = p;
        AP -= _p[0]->_state._position;
        Point3D<float> BP = p;
        BP -= _p[1]->_state._position;
        Point3D<float> CP = p;
        CP -= _p[2]->_state._position;

        Point3D<float> cPA = Point3D<float>::CrossProduct(AB, AP);
        Point3D<float> cPB = Point3D<float>::CrossProduct(BC, BP);
        Point3D<float> cPC = Point3D<float>::CrossProduct(CA, CP);

        float sAB = cPA.DotProduct(cPB);
        float sBC = cPB.DotProduct(cPC);
        float sCA = cPC.DotProduct(cPA);
        if ((0 > sAB) || (0 > sBC) || (0 > sCA))
        {
            return 0;
        }
        return 1;
    }

    int isInPrevTriangle(const Point3D<float>& p)
    {
        Point3D<float> AB = _p[1]->_prevState._position;
        AB -= _p[0]->_prevState._position;
        Point3D<float> BC = _p[2]->_prevState._position;
        BC -= _p[1]->_prevState._position;
        Point3D<float> CA = _p[0]->_prevState._position;
        CA -= _p[2]->_prevState._position;

        Point3D<float> AP = p;
        AP -= _p[0]->_prevState._position;
        Point3D<float> BP = p;
        BP -= _p[1]->_prevState._position;
        Point3D<float> CP = p;
        CP -= _p[2]->_prevState._position;

        Point3D<float> cPA = Point3D<float>::CrossProduct(AB, AP);
        Point3D<float> cPB = Point3D<float>::CrossProduct(BC, BP);
        Point3D<float> cPC = Point3D<float>::CrossProduct(CA, CP);

        float sAB = cPA.DotProduct(cPB);
        float sBC = cPB.DotProduct(cPC);
        float sCA = cPC.DotProduct(cPA);
        if ((0 > sAB) || (0 > sBC) || (0 > sCA))
        {
            return 0;
        }
        return 1;
    }

    Point3D<float> CalculatePrevProjection(const Point3D<float>& p)
    {
        float dP = _prevNormal.DotProduct(p);
        float sL = _prevNormal.getSquaredLength();
        float lambda = -1 * (_prevDCoeff + dP) / sL;
        Point3D<float> res(  p._x + lambda * _prevNormal._x
                           , p._y + lambda * _prevNormal._y
                           , p._z + lambda * _prevNormal._z);
        return res;
    }

    virtual void Draw(const DrawType&)
    {
        if (this->_highlighted)
        {
            glColor3f(1, 0, 0);
            DrawTriangle();
            glColor3f(1, 0.6, 0);
            return;
        }
        DrawTriangle();
    }

    inline void DrawTriangle()
    {
        DrawLine(_p[0]->_state._position, _p[1]->_state._position);
        DrawLine(_p[1]->_state._position, _p[2]->_state._position);
        DrawLine(_p[2]->_state._position, _p[0]->_state._position);
    }

    inline int isNeighbour(const ClothTriangle& other)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (this->_p[i] == other._p[j])
                {
                    return 1;
                }
            }
        }
        return 0;
    }
};

#endif // CLOTHTRIANGLE_H
