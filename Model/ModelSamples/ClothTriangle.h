#ifndef CLOTHTRIANGLE_H
#define CLOTHTRIANGLE_H


#include "Model/Interfaces/DrawableObject.h"
#include "Model/ModelSamples/Unresolved/Particle.h"

#include <iostream>
using namespace std;

class ClothTriangle: public DrawableObject
{
public:
    Particle* _p[3];
    Particle* _connected;

    int _highlighted;

    ClothTriangle(Particle* p1, Particle* p2, Particle *p3)
    {
        _p[0] = p1;
        _p[1] = p2;
        _p[2] = p3;
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
