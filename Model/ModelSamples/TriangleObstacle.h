#ifndef TRIANGLEOBSTACLE_H
#define TRIANGLEOBSTACLE_H

#include "Model/Interfaces/DrawableObject.h"
#include "Point3D.h"

class TriangleObstacle: public DrawableObject
{
public:
    TriangleObstacle(Point3D<float> p1, Point3D<float> p2, Point3D<float> p3);
    ~TriangleObstacle();
    void Draw();
private:
    Point3D<float> _points[3];
};

#endif // TRIANGLEOBSTACLE_H
