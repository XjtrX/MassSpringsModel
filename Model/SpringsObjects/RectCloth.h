#ifndef RECTCLOTH_H
#define RECTCLOTH_H

#include "SpringsObject.h"
class RectCloth: public SpringsObject
{
    friend void paintGL();
public:
    RectCloth(int cols, int rows, int width, int height
              , float massVolume, float stiffness, float borderRadius
              , Point3D<float> rotation, Point3D<float> translation);
    virtual ~RectCloth();
};

#endif // RECTCLOTH_H
