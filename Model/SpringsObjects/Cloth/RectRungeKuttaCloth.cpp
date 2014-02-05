#include "RectRungeKuttaCloth.h"

#include "3DMath/MathRotation.h"
#include "Model/ModelSamples/RungeKuttaParticle.h"

void ConnectParticles(Particle* p1, Particle* p2, Spring* s)
{
    dynamic_cast<RungeKuttaParticle*>(p1)->AddConnection(s, p2);
    dynamic_cast<RungeKuttaParticle*>(p2)->AddConnection(s, p1);
}

RectRungeKuttaCloth::RectRungeKuttaCloth(int cols, int rows, float width, float height
                                         , float massVolume, float stiffnes
                                         , float borderRadius
                                         , Point3D<float> rotation
                                         , Point3D<float> translation)
    : RungeKuttaSpringsObject(cols * rows
                  , (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1))
{
    //_particlesCount = cols * rows;: SpringsObject(particlesCount, springsCount)
    //_springsCount = (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1);
    //_particles = new particle[_particlesCount];
    //_springs = new Spring[_springsCount];

    float massOfParticle = massVolume / _particlesCount;

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
            _particles[r * cols + c] = new RungeKuttaParticle(
                        ParticleState(
                            m.RotateAndTranslatePoint(
                                Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows)
                                , rotMatr, translation), Point3D<float>(0, 0, 0))
                        , massOfParticle, borderRadius);
            if (c > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c - 1]
                        , _particles[r * cols + c]
                        , stiffnes, sW);

                ConnectParticles(_particles[r * cols + c - 1]
                        , _particles[r * cols + c]
                        , _springs[i - 1]);
            }
            if (r > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c]
                        , stiffnes, sH);

                ConnectParticles(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c]
                        , _springs[i - 1]);
            }
            if (c > 0 && r > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c - 1]
                        , stiffnes);

                ConnectParticles(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c - 1]
                        , _springs[i - 1]);

                _springs[i++] = new Spring(_particles[r * cols + c - 1]
                        , _particles[(r - 1) * cols + c]
                        , stiffnes);

                ConnectParticles(_particles[r * cols + c - 1]
                        , _particles[(r - 1) * cols + c]
                        , _springs[i - 1]);
            }
        }
    }
    delete[] rotMatr;
}

RectRungeKuttaCloth::~RectRungeKuttaCloth()
{
}
