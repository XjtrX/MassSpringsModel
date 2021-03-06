#include "PointTriangleManifold.h"

#include <math.h>

PointTriangleManifold::PointTriangleManifold(Particle *p, ClothTriangle *t)
{
    _p = p;
    _t = t;
}

PointTriangleManifold::~PointTriangleManifold()
{
}

void PointTriangleManifold::ResolveCollisionByMomentumConversation(const float&)
{
    Point3D<float>& D = _p->_state._position;

    this->_t->RecalculatePlane();
    Point3D<float> projection = _t->CalculateProjection(D);
    Point3D<float> bCPr = projection.BarycentricCoordinates(
              this->_t->_p[0]->_state._position
            , this->_t->_p[1]->_state._position
            , this->_t->_p[2]->_state._position);

    Point3D<float> velP = _p->_averageVelocity;

    Point3D<float> velT0 = _t->_p[0]->_averageVelocity;

    Point3D<float> velT1 = _t->_p[1]->_averageVelocity;

    Point3D<float> velT2 = _t->_p[2]->_averageVelocity;

    velT0 *= bCPr._x;
    velT1 *= bCPr._y;
    velT2 *= bCPr._z;

    Point3D<float> velT = velT0;
    velT += velT1;
    velT += velT2;

    Point3D<float> dispVel = velP;
    dispVel -= velT;

    float mP = _p->_massVolume;
    float mT = _t->_p[0]->_massVolume + _t->_p[1]->_massVolume + _t->_p[2]->_massVolume;

    Point3D<float> vPRes = (velP * (mP - mT) + velT * (2 * mT)) / (mP + mT);

    Point3D<float> vTRes = (velT * (mT - mP) + velP * (2 * mP)) / (mP + mT);

    _p->_approximateVelocity = vPRes;
    _t->_p[0]->_approximateVelocity = vTRes * bCPr._x;
    _t->_p[1]->_approximateVelocity = vTRes * bCPr._y;
    _t->_p[2]->_approximateVelocity = vTRes * bCPr._z;

    _p->_collided = 1;
    _t->_p[0]->_collided = 1;
    _t->_p[1]->_collided = 1;
    _t->_p[2]->_collided = 1;
}

#include <iostream>
using namespace std;

void PointTriangleManifold::ResolveCollisionByProvot(const float &)
{
    Point3D<float>& D = _p->_state._position;

    this->_t->RecalculatePlane();
    Point3D<float> projection = _t->CalculateProjection(D);
    Point3D<float> bCPr = projection.BarycentricCoordinates(
              this->_t->_p[0]->_state._position
            , this->_t->_p[1]->_state._position
            , this->_t->_p[2]->_state._position);

    Point3D<float> velP = _p->_averageVelocity;

    Point3D<float> velT0 = _t->_p[0]->_averageVelocity;

    Point3D<float> velT1 = _t->_p[1]->_averageVelocity;

    Point3D<float> velT2 = _t->_p[2]->_averageVelocity;

    velT0 *= bCPr._x;
    velT1 *= bCPr._y;
    velT2 *= bCPr._z;

    Point3D<float> velT = velT0;
    velT += velT1;
    velT += velT2;

    Point3D<float> dispVel = velP;
    dispVel -= velT;

    Point3D<float> normal = _t->_normal;
    Point3D<float> dispVNp = normal * normal.DotProduct(dispVel);
    Point3D<float> dispVTp = dispVel - dispVNp;

    _p->_collided = 1;

    float kd = 0.8;
    float kf = 1;

    if (dispVTp.getSquaredLength() >= kf * kf * dispVNp.getSquaredLength())
    {
        _p->_approximateVelocity = dispVTp * (1 - kf * sqrt(dispVNp.getSquaredLength() / dispVTp.getSquaredLength())) - dispVNp * kd + velT;
//        cout << "sliding\n";
    }
    else
    {
        _p->_approximateVelocity = dispVNp * (-1 * kd) + velT;
//        cout << "non-sliding\n";
    }
    cout.flush();
}
