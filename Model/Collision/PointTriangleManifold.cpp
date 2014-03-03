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

void PointTriangleManifold::ResolveCollision(const float& timestep)
{
    Point3D<float>& D = _p->_state._position;

    this->_t->RecalculatePlane();
    Point3D<float> projection = _t->CalculateProjection(D);
    Point3D<float> bCPr = projection.BarycentricCoordinates(
              this->_t->_p[0]->_state._position
            , this->_t->_p[1]->_state._position
            , this->_t->_p[2]->_state._position);
    Point3D<float> disp = D;
    disp -= projection;

//    /*
    Point3D<float> velP = _p->_state._velocity;

    Point3D<float> velT0 = _t->_p[0]->_state._velocity;

    Point3D<float> velT1 = _t->_p[1]->_state._velocity;

    Point3D<float> velT2 = _t->_p[2]->_state._velocity;
//    */
    /*
    Point3D<float> velP = _p->_averageVelocity;

    Point3D<float> velT0 = _t->_p[0]->_averageVelocity;

    Point3D<float> velT1 = _t->_p[1]->_averageVelocity;

    Point3D<float> velT2 = _t->_p[2]->_averageVelocity;
    */
//    /*
    velP *= timestep;
    velT0 *= timestep;
    velT1 *= timestep;
    velT2 *= timestep;
//    */
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


    _p->setVelocity(vPRes, timestep);
    _t->_p[0]->setVelocity(vTRes * bCPr._x, timestep);
    _t->_p[1]->setVelocity(vTRes * bCPr._y, timestep);
    _t->_p[2]->setVelocity(vTRes * bCPr._z, timestep);

    return;















    float coeff = -500 * sqrt(dispVel.getSquaredLength()) * _p->_massVolume;

    disp *= coeff;



    _p->ApplyForce(disp._x, disp._y, disp._z);
//    return;
    disp *= -1;
    _t->_p[0]->ApplyForce(disp._x * bCPr._x, disp._y * bCPr._x, disp._z * bCPr._x);
    _t->_p[1]->ApplyForce(disp._x * bCPr._y, disp._y * bCPr._y, disp._z * bCPr._y);
    _t->_p[2]->ApplyForce(disp._x * bCPr._z, disp._y * bCPr._z, disp._z * bCPr._z);
}
