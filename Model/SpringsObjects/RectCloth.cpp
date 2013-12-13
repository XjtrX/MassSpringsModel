#include "RectCloth.h"

RectCloth::RectCloth(int cols, int rows, int width, int height, float stiffnes)
    : SpringsObject(cols * rows
                  , (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1))
{
    //_particlesCount = cols * rows;
    //_springsCount = (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1);
    //_particles = new Particle[_particlesCount];
    //_springs = new Spring[_springsCount];

    float sW = 1.0 * width / cols;
//    float sMW = sW * 2;
    float sH = 1.0 * height / rows;
//    float sMH = sH * 2;

    int i = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            _particles[r * cols + c] = Particle(
                        Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows));
            if (c > 0)
            {
                _springs[i++] = Spring(&_particles[r * cols + c - 1], &_particles[r * cols + c]
                        , stiffnes, sW);
            }
            if (r > 0)
            {
                _springs[i++] = Spring(&_particles[r * cols + c], &_particles[(r - 1) * cols + c]
                        , stiffnes, sH);
            }
            if (c > 0 && r > 0)
            {
                _springs[i++] = Spring(&_particles[r * cols + c], &_particles[(r - 1) * cols + c - 1]
                        , stiffnes);
                _springs[i++] = Spring(&_particles[r * cols + c - 1], &_particles[(r - 1) * cols + c]
                        , stiffnes);
            }
        }
    }
}

RectCloth::~RectCloth()
{
}