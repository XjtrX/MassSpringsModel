#include "PointTriangleMainfold.h"

#include <math.h>

PointTriangleMainfold::PointTriangleMainfold(Particle *p, ClothTriangle *t)
{
    _p = p;
    _t = t;
}

PointTriangleMainfold::~PointTriangleMainfold()
{
}

void PointTriangleMainfold::ResolveCollision()
{
    Point3D<float>& D = _p->_position._position;

    this->_t->RecalculatePlane();
    Point3D<float> projection = _t->CalculateProjection(D);
    projection.Print("projection");
    Point3D<float> bCPr = projection.BarycentricCoordinates(
              this->_t->_p[0]->_position._position
            , this->_t->_p[1]->_position._position
            , this->_t->_p[2]->_position._position);
//    bCPr.Print("barycentricProjection");
    Point3D<float> disp = D;
    disp -= projection;

//    disp.Print("disp");

    float coeff = 0.2;

    disp *= coeff;

    _p->ApplyForce(disp._x, disp._y, disp._z);
//    return;
    disp *= -1;
    _t->_p[0]->ApplyForce(disp._x * bCPr._x, disp._y * bCPr._x, disp._z * bCPr._x);
    _t->_p[1]->ApplyForce(disp._x * bCPr._y, disp._y * bCPr._y, disp._z * bCPr._y);
    _t->_p[2]->ApplyForce(disp._x * bCPr._z, disp._y * bCPr._z, disp._z * bCPr._z);
}
