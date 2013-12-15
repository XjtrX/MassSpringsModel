#include "TriangleObstacle.h"
#include <GL/glut.h>
#include "3DMath/MathRotation.h"

TriangleObstacle::TriangleObstacle(float width, float height
                                   , Point3D<float> rotHold
                                   , const Point3D<float> &translation)

{
    MathRotation m;
    _rotMatr = m.RotationMatrix(rotHold.getX(), rotHold.getY(), rotHold.getZ());
    _points[0].set(0, 0, 0);
    _points[1].set(width, 0, 0);
    _points[2].set(0, height, 0);

    _translation = translation;

    _rotPoints[0] = m.RotateAndTranslatePoint(_points[0], _rotMatr, _translation);
    _rotPoints[1] = m.RotateAndTranslatePoint(_points[1], _rotMatr, _translation);
    _rotPoints[2] = m.RotateAndTranslatePoint(_points[2], _rotMatr, _translation);
}

TriangleObstacle::~TriangleObstacle()
{
    delete _rotMatr;
}

void TriangleObstacle::Draw()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(_rotPoints[0].getX(), _rotPoints[0].getY(), _rotPoints[0].getZ());
    glVertex3f(_rotPoints[1].getX(), _rotPoints[1].getY(), _rotPoints[1].getZ());
    glVertex3f(_rotPoints[2].getX(), _rotPoints[2].getY(), _rotPoints[2].getZ());
    glEnd();
}
