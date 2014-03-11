#ifndef TRIANGLESMANIFOLD_H
#define TRIANGLESMANIFOLD_H

#include"Model/ModelSamples/ClothTriangle.h"

#include <vector>
using namespace std;

class TrianglesManifold
{
public:
    TrianglesManifold(const vector<ClothTriangle*>& triangles);
    virtual ~TrianglesManifold();

    void Compute();

public:
    vector<Particle*> _particles;

    Point3D<float> _xCM;
    Point3D<float> _vCM;
    Point3D<float> _L;
};

#endif // TRIANGLESMANIFOLD_H
