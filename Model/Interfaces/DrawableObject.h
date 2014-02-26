#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "3DMath/Point3D.h"
#include <GL/glut.h>

enum DrawType
{
    lines,
    triangles
};

class DrawableObject
{
public:
    virtual void Draw(const DrawType& type) = 0;

    inline static void DrawLine(Point3D<float>& a, Point3D<float>& b)
    {
        glVertex3f(a._x, a._y, a._z);
        glVertex3f(b._x, b._y, b._z);
    }

};

#endif // DRAWABLEOBJECT_H
