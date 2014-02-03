#ifndef RECTRUNGEKUTTACLOTH_H
#define RECTRUNGEKUTTACLOTH_H

#include "Model/SpringsObjects/RungeKuttaSpringsObject.h"

class RectRungeKuttaCloth: public RungeKuttaSpringsObject
{
public:
    RectRungeKuttaCloth(int cols, int rows, int width, int height
              , float massVolume, float stiffnes, float borderRadius
              , Point3D<float> rotation, Point3D<float> translation);
    virtual ~RectRungeKuttaCloth();
};

#endif // RECTRUNGEKUTTACLOTH_H
