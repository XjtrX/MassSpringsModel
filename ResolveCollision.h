#ifndef RESOLVECOLLISION_H
#define RESOLVECOLLISION_H

#include "Model/ModelSamples/Spring.h"

void SpingSpringsCollide(Spring* a, Spring* b)
{

}

/*
Если каноническое уравнение прямой 0:
(x-xo)/p=(y-yo)/q=(z-zo)/r
а каноническое уравнение прямой 1:
(x-x1)/p1=(y-y1)/q1=(z-z1)/r1

То координаты их точки пересечения:


x=(xo*q*p1-x1*q1*p-yo*p*p1+y1*p*p1)/(q*p1-q1*p)
y=(yo*p*q1-y1*p1*q-xo*q*q1+x1*q*q1)/(p*q1-p1*q)
z=(zo*q*r1-z1*q1*r-yo*r*r1+y1*r*r1)/(q*r1-q1*r)
*/

int areIntesecting(Spring* a, Spring* b, Point3D<float>* intersectionPoint)
{
    Point3D<float>* aAP = a->_particleA->_position;
    Point3D<float>* aBP = a->_particleB->_position;

    Point3D<float>* bAP = b->_particleA->_position;
    Point3D<float>* bBP = b->_particleB->_position;

    float x0 = aAP->_x;
    float y0 = aAP->_y;
    float z0 = aAP->_z;

    float p = aBP->_x - x0;
    float q = aBP->_y - y0;
    float r = aBP->_z - z0;

    float x1 = bAP->_x;
    float y1 = bAP->_y;
    float z1 = bAP->_z;

    float p1 = bBP->_x - x0;
    float q1 = bBP->_y - y0;
    float r1 = bBP->_z - z0;

    float xN = xo*q*p1-x1*q1*p-yo*p*p1+y1*p*p1;
    float yN = yo*p*q1-y1*p1*q-xo*q*q1+x1*q*q1;
    float zN = zo*q*r1-z1*q1*r-yo*r*r1+y1*r*r1;

    float xD = q * p1 - q1 * p;
    float yD = p * q1-p1 * q;
    float zD = q * r1 - q1 * r;

    if (   !xN && !yN && !zN
        && !xD && !yD && !zD)
    {
        return false;
    }

    intersectionPoint->_x = xN / xD;
    intersectionPoint->_y = yN / yD;
    intersectionPoint->_z = zN / zD;
}

#endif // RESOLVECOLLISION_H
