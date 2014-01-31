#ifndef RECTCLOTH_H
#define RECTCLOTH_H

#include "VerletSpringsObject.h"
class RectVerletCloth: public VerletSpringsObject
{
    friend void paintGL();
public:
    RectVerletCloth(int cols, int rows, int width, int height
              , float massVolume, float stiffness, float borderRadius
              , Point3D<float> rotation, Point3D<float> translation);
    virtual ~RectVerletCloth();
};

#endif // RECTCLOTH_H
