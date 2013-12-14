#include "TriangleObstacle.h"
#include <GL/glut.h>

TriangleObstacle::TriangleObstacle(Point3D<float> p1, Point3D<float> p2, Point3D<float> p3)
{
}

TriangleObstacle::~TriangleObstacle()
{
}

void TriangleObstacle::Draw()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(_points[0].getX(), _points[0].getY(), _points[0].getZ());
    glVertex3f(_points[1].getX(), _points[1].getY(), _points[1].getZ());
    glVertex3f(_points[2].getX(), _points[2].getY(), _points[2].getZ());
    glEnd();
}
