#ifndef RECTCLOTH_H
#define RECTCLOTH_H

#include "SpringsObject.h"
class RectCloth: public SpringsObject
{
    friend void paintGL();
public:
    RectCloth(int cols, int rows, int width, int height, float stiffness);
    ~RectCloth();
};

#endif // RECTCLOTH_H
