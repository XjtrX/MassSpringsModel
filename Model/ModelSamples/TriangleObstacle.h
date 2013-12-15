#ifndef TRIANGLEOBSTACLE_H
#define TRIANGLEOBSTACLE_H

#include "Model/Interfaces/DrawableObject.h"
#include "3DMath/RotationHolder.h"

class TriangleObstacle: public DrawableObject
{
public:
    TriangleObstacle(float width, float height, Point3D<float> rotHold
                     , const Point3D<float> &translation);
    virtual ~TriangleObstacle();
    void Draw();
private:
    float* _rotMatr;
    Point3D<float> _translation;
    Point3D<float> _points[3];
    Point3D<float> _rotPoints[3];
};

#endif // TRIANGLEOBSTACLE_H
