#ifndef RECTVERLETCLOTH_H
#define RECTVERLETCLOTH_H

#include "Model/SpringsObjects/VerletSpringsObject.h"

class RectVerletCloth: public VerletSpringsObject
{
    friend void paintGL();
public:
    RectVerletCloth(int cols, int rows, int width, int height
              , float massVolume, float stiffness, float borderRadius
              , Point3D<float> rotation, Point3D<float> translation);
    virtual ~RectVerletCloth();
};

#endif // RECTVERLETCLOTH_H
