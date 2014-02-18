#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "3DMath/Point3D.h"
#include <GL/glut.h>

class DrawableObject
{
public:
    virtual void Draw() = 0;
};

#endif // DRAWABLEOBJECT_H
