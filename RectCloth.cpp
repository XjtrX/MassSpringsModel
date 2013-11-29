#include "RectCloth.h"

RectCloth::RectCloth(int colls, int rows, int width, int height)
    : _mass(colls * rows)
    , _sprigs((colls - 1) * rows + colls * (rows - 1))
{
    int i = 0;
    float sW = 1.0 * width / colls;
    float sMW = sW * 2;
    float sH = 1.0 * height / rows;
    float sMH = sH * 2;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < colls; c++)
        {
            _mass[r * colls + c] = Mass(Point3D<float>(1.0 * width * c / colls, 1.0 * height * r / rows), 1.0, 0);
            if (c > 0)
            {
                _sprigs[i++] = Spring(&_mass[r * colls + c - 1], &_mass[r * colls + c], sW, sMW, 1000);
            }
            if (r > 0)
            {
                _sprigs[i++] = Spring(&_mass[r * colls + c], &_mass[(r - 1) * colls + c], sH, sMH, 1000);
            }

//
//                        points[r * COLS + c] = new Point(c * 10, r * 10);
//                        if (c > 0) {
//                            sticks[i++] = new Stick(points[r * COLS + c - 1], points[r * COLS + c]);
//                        }
//                        if (r > 0) {
//                            sticks[i++] = new Stick(points[r * COLS + c], points[(r - 1)* COLS + c]);
//                        }
//
        }
    }
}

RectCloth::~RectCloth()
{
}
