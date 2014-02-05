#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <GL/glut.h>
class DrawableObject
{
    virtual void Draw(const int& flushColor) = 0;
};

#endif // DRAWABLEOBJECT_H
