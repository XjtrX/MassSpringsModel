#ifndef CLOTHTRIANGLE_H
#define CLOTHTRIANGLE_H


#include "Model/Interfaces/DrawableObject.h"
#include "Model/ModelSamples/Unresolved/Particle.h"

class ClothTriangle: public DrawableObject
{
public:
    Particle* _p1;
    Particle* _p2;
    Particle* _p3;
    Particle* _connected;

    int _highlighted;

    ClothTriangle(Particle* p1, Particle* p2, Particle *p3)
    {
        _p1 = p1;
        _p2 = p2;
        _p3 = p3;
        _highlighted = 0;
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

    inline void DrawLine(Point3D<float>& a, Point3D<float>& b)
    {
        glVertex3f(a._x, a._y, a._z);
        glVertex3f(b._x, b._y, b._z);
    }

    inline void DrawTriangle()
    {
        DrawLine(_p1->_position._position, _p2->_position._position);
        DrawLine(_p2->_position._position, _p2->_position._position);
        DrawLine(_p3->_position._position, _p1->_position._position);
    }
};

#endif // CLOTHTRIANGLE_H
