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
//    projection.Print("projection");
    Point3D<float> bCPr = projection.BarycentricCoordinates(
              this->_t->_p[0]->_state._position
            , this->_t->_p[1]->_state._position
            , this->_t->_p[2]->_state._position);
//    bCPr.Print("barycentricProjection");
    Point3D<float> disp = D;
    disp -= projection;

//    disp.Normalization();
//    float coeff = -0.0000010;

    /*
    Point3D<float> velP = _p->_state._position;
    velP -= _p->_prevState._position;

    Point3D<float> velT0 = _t->_p[0]->_state._position;
    velT0 -= _t->_p[0]->_prevState._position;

    Point3D<float> velT1 = _t->_p[1]->_state._position;
    velT1 -= _t->_p[1]->_prevState._position;

    Point3D<float> velT2 = _t->_p[2]->_state._position;
    velT2 -= _t->_p[2]->_prevState._position;
    */

//    /*
    Point3D<float> velP = _p->_state._velocity;

    Point3D<float> velT0 = _t->_p[0]->_state._velocity;

    Point3D<float> velT1 = _t->_p[1]->_state._velocity;

    Point3D<float> velT2 = _t->_p[2]->_state._velocity;
//    */

    /*
    Point3D<float> velT0 = dynamic_cast<RungeKuttaParticle*>(_t->_p[0])->_interm._velocity;

    Point3D<float> velT1 = dynamic_cast<RungeKuttaParticle*>(_t->_p[1])->_interm._velocity;

    Point3D<float> velT2 = dynamic_cast<RungeKuttaParticle*>(_t->_p[2])->_interm._velocity;
    */

    velP *= timestep;
    velT0 *= timestep;
    velT1 *= timestep;
    velT2 *= timestep;

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

    /*
    if (!_p->_static)
    {
        _p->_prevState._position = _p->_state._position - vPRes / 25;
    }

    if (!_t->_p[0]->_static)
    {
        _t->_p[0]->_prevState._position = _t->_p[0]->_state._position - vTRes / 25 * bCPr._x;
    }
    if (!_t->_p[1]->_static)
    {
        _t->_p[1]->_prevState._position = _t->_p[1]->_state._position - vTRes / 25 * bCPr._y;
    }
    if (!_t->_p[2]->_static)
    {
        _t->_p[2]->_prevState._position = _t->_p[2]->_state._position - vTRes / 25 * bCPr._z;
    }
    */
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
