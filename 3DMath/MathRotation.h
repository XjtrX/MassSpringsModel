#ifndef MATHROTATION_H
#define MATHROTATION_H

#define PI 3.14159265

#include <math.h>
using namespace std;

#include "3DMath/Point3D.h"

float* rotX(const float &x)
{
    float* rotX = new float[9];

    double angle = x * PI / 180;

    rotX[0] = 1;
    rotX[3] = 0;
    rotX[6] = 0;

    rotX[1] = 0;
    rotX[4] = cos(angle);
    rotX[7] = -1 * sin (angle);

    rotX[2] = 0;
    rotX[5] = sin(angle);
    rotX[8] = cos(angle);

    return rotX;
}

float* rotY(const float &y)
{
    float* rotY = new float[9];

    double angle = y * PI / 180;

    rotY[0] = cos(angle);
    rotY[3] = 0;
    rotY[6] = sin(angle);

    rotY[1] = 0;
    rotY[4] = 1;
    rotY[7] = 0;

    rotY[2] = -1 * sin(angle);
    rotY[5] = 0;
    rotY[8] = cos(angle);

    return rotY;
}

float* rotZ(const float &z)
{
    float* rotZ = new float[9];

    double angle = z * PI / 180;

    rotZ[0] = cos(angle);
    rotZ[3] = -1 * sin(angle);
    rotZ[6] = 0;

    rotZ[1] = sin(angle);
    rotZ[4] = cos(angle);
    rotZ[7] = 0;

    rotZ[2] = 0;
    rotZ[5] = 0;
    rotZ[8] = 1;

    return rotZ;
}

float* MultRotMatr(const float* m1, const float* m2)
{
    float* res = new float[9];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float sum = 0;
            for (int k = 0; k < 3; k++)
            {
                sum += m1[k * 3 + j] * m2[i * 3 + k];
            }
            res[i * 3 + j] = sum;
        }
    }
    return res;
}

Point3D<float>& RotatePoint(Point3D<float> &p, const float *rotMart)
{
    Point3D<float>* res = new Point3D<float>();
    res->setX(p.getX() * rotMart[0] + p.getY() * rotMart[1] + p.getZ() * rotMart[2]);
    res->setY(p.getX() * rotMart[3] + p.getY() * rotMart[4] + p.getZ() * rotMart[5]);
    res->setZ(p.getX() * rotMart[6] + p.getY() * rotMart[7] + p.getZ() * rotMart[8]);
    return *res;
}

Point3D<float>& RotateAndTranslatePoint(Point3D<float> &p, const float *rotMart
                                        , Point3D<float> &tr)
{
    Point3D<float>* res = new Point3D<float>();
    res->setX(p.getX() * rotMart[0] + p.getY() * rotMart[1] + p.getZ() * rotMart[2] + tr.getX());
    res->setY(p.getX() * rotMart[3] + p.getY() * rotMart[4] + p.getZ() * rotMart[5] + tr.getY());
    res->setZ(p.getX() * rotMart[6] + p.getY() * rotMart[7] + p.getZ() * rotMart[8] + tr.getZ());
    return *res;
}

float* RotationMatrix(const float &x, const float &y, const float &z)
{
    float* rX = rotX(x);
    float* rY = rotY(y);
    float* rZ = rotZ(z);

    float* rXY = MultRotMatr(rX, rY);
    float* rXYZ = MultRotMatr(rXY, rZ);

    delete[] rX;
    delete[] rY;
    delete[] rZ;
    delete[] rXY;

    return rXYZ;
}

#endif // MATHROTATION_H
