#ifndef CLOTHTRIANGLE_H
#define CLOTHTRIANGLE_H


#include "Model/Interfaces/DrawableObject.h"
#include "Model/ModelSamples/Unresolved/Particle.h"

class ClothTriangle: public DrawableObject
{
public:
    Particle* _p[3];
    Particle* _connected;

    Point3D<float> _normal;
    float _DCoeff;

    int _highlighted;

    ClothTriangle(Particle* p1, Particle* p2, Particle *p3)
    {
        _p[0] = p1;
        _p[1] = p2;
        _p[2] = p3;
        _highlighted = 0;
    }

    virtual ~ClothTriangle()
    {

    }

    void RecalculatePlane()
    {
        Point3D<float>& A = this->_p[0]->_position._position;
        Point3D<float>& B = this->_p[1]->_position._position;
        Point3D<float>& C = this->_p[2]->_position._position;

        Point3D<float> AB = B;
        AB -= A;

        Point3D<float> AC = C;
        AC -= A;

        this->_normal = Point3D<float>::CrossProduct(AB, AC);

        _DCoeff = this->_normal.DotProduct(A);
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

    virtual void Draw()
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
        DrawLine(_p[0]->_position._position, _p[1]->_position._position);
        DrawLine(_p[1]->_position._position, _p[2]->_position._position);
        DrawLine(_p[2]->_position._position, _p[0]->_position._position);
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
