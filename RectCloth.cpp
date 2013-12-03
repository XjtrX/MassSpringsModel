#include "RectCloth.h"
/*
RectCloth::RectCloth(int colls, int rows, int width, int height)
{
    int i = 0;
    float sW = 1.0 * width / colls;
    float sMW = sW * 2;
    float sH = 1.0 * height / rows;
    float sMH = sH * 2;


    _massesCount = colls * rows;
    _springsCount = (colls - 1) * rows + colls * (rows - 1);
    _masses = new Mass[_massesCount];
    _springs = new Spring[_springsCount];
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < colls; c++)
        {
            _masses[r * colls + c] = Mass(Point3D<float>(1.0 * width * c / colls, 1.0 * height * r / rows), 1.0, 0);
            if (c > 0)
            {
                _springs[i++] = Spring(&_masses[r * colls + c - 1], &_masses[r * colls + c], sW, sMW, 1);
            }
            if (r > 0)
            {
                _springs[i++] = Spring(&_masses[r * colls + c], &_masses[(r - 1) * colls + c], sH, sMH, 1);
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
*/

#include <iostream>
using namespace std;

RectCloth::RectCloth(int cols, int rows, int width, int height)
{
    _particlesCount = cols * rows;
    _springsCount = (cols - 1) * rows + cols * (rows - 1);
    _particles = new Particle[_particlesCount];
    _springs = new Spring[_springsCount];

    int i = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            _particles[r * cols + c] = Particle("particle " + (r*cols + c));
            if (c > 0)
            {
                _springs[i++] = Spring(&_particles[r * cols + c - 1], &_particles[r * cols + c], " spring " + (i - 1));
            }
            if (r > 0)
            {
                _springs[i++] = Spring(&_particles[r * cols + c], &_particles[(r - 1) * cols + c], " spring " + (i-1));
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

    for (int l = 0; l < _particlesCount; l++)
    {
        cout << _particles[l]._str << endl;
    }

}

RectCloth::~RectCloth()
{
    //
}
