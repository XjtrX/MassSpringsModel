#ifndef RECTVERLETCLOTH_H
#define RECTVERLETCLOTH_H

#include "Model/SpringsObjects/VerletSpringsObject.h"

class RectVerletCloth: public VerletSpringsObject
{
    friend void paintGL();
public:  
    RectVerletCloth(int cols, int rows, float width, float height
              , float massVolume, float stiffness, float borderRadius
              , Point3D<float> rotation, Point3D<float> translation
              , const int& withBendSprings);
    virtual ~RectVerletCloth();
};

#endif // RECTVERLETCLOTH_H
