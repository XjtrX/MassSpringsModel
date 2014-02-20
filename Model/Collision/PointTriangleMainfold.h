#ifndef POINTTRIANGLEMAINFOLD_H
#define POINTTRIANGLEMAINFOLD_H

#include "Model/ModelSamples/ClothTriangle.h"

class PointTriangleMainfold
{
public:
    Particle* _p;
    ClothTriangle* _t;
    Point3D<float> _barycentric;
public:
    PointTriangleMainfold(Particle* p, ClothTriangle* t);
    virtual ~PointTriangleMainfold();

    void ResolveCollision();
};

#endif // POINTTRIANGLEMAINFOLD_H
