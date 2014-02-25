#ifndef POINTTRIANGLEMANIFOLD_H
#define POINTTRIANGLEMANIFOLD_H

#include "Model/ModelSamples/ClothTriangle.h"

class PointTriangleManifold
{
public:
    Particle* _p;
    ClothTriangle* _t;
    Point3D<float> _barycentric;
public:
    PointTriangleManifold(Particle* p, ClothTriangle* t);
    virtual ~PointTriangleManifold();

    void ResolveCollision();
};

#endif // POINTTRIANGLEMANIFOLD_H
