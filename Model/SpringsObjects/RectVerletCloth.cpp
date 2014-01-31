#include "RectVerletCloth.h"
#include "3DMath/MathRotation.h"
#include "Model/ModelSamples/VerletParticle.h"

RectVerletCloth::RectVerletCloth(int cols, int rows, int width, int height
                     , float massVolume, float stiffnes, float borderRadius
                     , Point3D<float> rotation, Point3D<float> translation)
    : VerletSpringsObject(cols * rows
                  , (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1))
{
    //_particlesCount = cols * rows;
    //_springsCount = (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1);
    //_particles = new particle[_particlesCount];
    //_springs = new Spring[_springsCount];

    float massOfVerletParticle = massVolume / _particlesCount;

    float sW = 1.0 * width / (cols - 1);
//    float sMW = sW * 2;
    float sH = 1.0 * height / (rows - 1);
//    float sMH = sH * 2;
    MathRotation m;
    float* rotMatr = m.RotationMatrix(rotation.getX()
                                                 , rotation.getY()
                                                 , rotation.getZ());
    int i = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            _particles[r * cols + c] = new VerletParticle(
                        ParticlePosition(
                            m.RotateAndTranslatePoint(
                                Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows)
                                , rotMatr, translation))
                        , massOfVerletParticle, borderRadius);
            if (c > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c - 1], _particles[r * cols + c]
                        , stiffnes, sW);
            }
            if (r > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c], _particles[(r - 1) * cols + c]
                        , stiffnes, sH);
            }
            if (c > 0 && r > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c], _particles[(r - 1) * cols + c - 1]
                        , stiffnes);
                _springs[i++] = new Spring(_particles[r * cols + c - 1], _particles[(r - 1) * cols + c]
                        , stiffnes);
            }
        }
    }
    delete[] rotMatr;
}

RectVerletCloth::~RectVerletCloth()
{
}
