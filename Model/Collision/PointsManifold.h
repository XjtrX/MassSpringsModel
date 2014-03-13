#ifndef POINTSMANIFOLD_H
#define POINTSMANIFOLD_H

#include "Model/ModelSamples/ClothTriangle.h"
#include "3DMath/Matrix3x3D.h"

#include <vector>
using namespace std;

class PointsManifold
{
public:
    PointsManifold(const vector<ClothTriangle*>& triangles);
    virtual ~PointsManifold();

    void ComputeAngularMomentum();

    void RecalculatePoinsState(const float& timestep);

public:
    vector<Particle*> _particles;

    Point3D<float> _xCM;
    Point3D<float> _vCM;
    Point3D<float> _L;
    Matrix3x3D<float> _I;
    Point3D<float> _omega;
};

#endif // POINTSMANIFOLD_H
